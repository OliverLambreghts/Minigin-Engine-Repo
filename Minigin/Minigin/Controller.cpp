#include "MiniginPCH.h"

#include "Controller.h"
#include <algorithm>
#include <climits>

#include "InputManager.h"

dae::Controller::Controller(UINT id)
	: m_ID{ id },
	m_DeadZoneX(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE),
	m_DeadZoneY(XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
{
	ZeroMemory(&m_State, sizeof(XINPUT_STATE));
	ZeroMemory(&m_Stroke, sizeof(XINPUT_KEYSTROKE));
}

UINT dae::Controller::GetID() const
{
	return m_ID;
}

XINPUT_GAMEPAD* dae::Controller::GetGamePad()
{
	return &m_State.Gamepad;
}

bool dae::Controller::IsConnected()
{
	if (XInputGetState(m_ID, &m_State) == ERROR_SUCCESS)
		return true;
	return false;
}

bool dae::Controller::IsButtonPressed(dae::ControllerButton button) const
{
	if (button == ControllerButton::ButtonA)
		return (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0;
	if (button == ControllerButton::ButtonB)
		return (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0;
	if (button == ControllerButton::ButtonX)
		return (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_X) != 0;
	if (button == ControllerButton::ButtonY)
		return (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0;
	if (button == ControllerButton::ButtonLeft)
		return (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0;
	if (button == ControllerButton::ButtonRight)
		return (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0;
	if (button == ControllerButton::ButtonUp)
		return (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0;
	return (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0;
}

bool dae::Controller::IsButtonPressed(ControllerButton button, WORD keyStroke) const
{
	if(m_Stroke.Flags == keyStroke)
	{
		if (m_Stroke.VirtualKey == (WORD)button)
			return true;
	}
	return false;
}

bool dae::Controller::Update()
{
	if (!IsConnected())
		return false;
	XInputGetKeystroke(m_ID, 0, &m_Stroke);

	float normLX = Normalize(static_cast<float>(m_State.Gamepad.sThumbLX), -32767.f, 32767.f);
	float normLY = Normalize(static_cast<float>(m_State.Gamepad.sThumbLY), -32767.f, 32767.f);

	float normRX = Normalize(static_cast<float>(m_State.Gamepad.sThumbRX), -32767.f, 32767.f);
	float normRY = Normalize(static_cast<float>(m_State.Gamepad.sThumbRY), -32767.f, 32767.f);

	if (m_DeadZoneX <= 1.f || m_DeadZoneY <= 1.f)
	{
		m_LeftStickX = ApplyDeadzone(normLX, m_MaxValue, m_DeadZoneX);
		m_LeftStickY = ApplyDeadzone(normLY, m_MaxValue, m_DeadZoneY);
		m_RightStickX = ApplyDeadzone(normRX, m_MaxValue, m_DeadZoneX);
		m_RightStickY = ApplyDeadzone(normRY, m_MaxValue, m_DeadZoneY);
	}
	else
	{
		m_LeftStickX = ApplyDeadzone(normLX, m_MaxValue, Normalize(m_DeadZoneX, SHRT_MIN, SHRT_MAX));
		m_LeftStickY = ApplyDeadzone(normLY, m_MaxValue, Normalize(m_DeadZoneY, SHRT_MIN, SHRT_MAX));
		m_RightStickX = ApplyDeadzone(normRX, m_MaxValue, Normalize(m_DeadZoneX, SHRT_MIN, SHRT_MAX));
		m_RightStickY = ApplyDeadzone(normRY, m_MaxValue, Normalize(m_DeadZoneY, SHRT_MIN, SHRT_MAX));
	}

	m_LeftTrigger = static_cast<float>(m_State.Gamepad.bLeftTrigger) / 255.f;
	m_RightTrigger = static_cast<float>(m_State.Gamepad.bRightTrigger) / 255.f;
	return true;
}

float dae::Controller::ApplyDeadzone(float value, float maxValue, float deadZone)
{
	if (value < -deadZone)
		value += deadZone;
	else if (value > deadZone)
		value -= deadZone;
	else
		return 0.f;
	float normValue = float(value) / float(maxValue - deadZone);
	return (std::max)(-1.0f, (std::min)(normValue, 1.0f));
}

float dae::Controller::Normalize(float input, float min, float max)
{
	float average = (min + max) / 2.f;
	float range = (max - min) / 2.f;
	return (input - average) / range;
}