#pragma once
#include "Windows.h"
#include "Xinput.h"

namespace dae
{
	enum class ControllerButton;

	class Controller
	{
	public:
		Controller(UINT id);

		bool Update();

		UINT GetID() const;
		XINPUT_GAMEPAD* GetGamePad();

		bool IsConnected();
		bool IsButtonPressed(ControllerButton button) const;
		bool IsButtonPressed(ControllerButton button, WORD keyStroke) const;
	private:
		UINT m_ID;

		const float m_MaxValue = 1.f;
		float m_DeadZoneX, m_DeadZoneY;
		XINPUT_STATE m_State;
		XINPUT_KEYSTROKE m_Stroke;

		float m_LeftStickX, m_LeftStickY;
		float m_RightStickX, m_RightStickY;
		float m_LeftTrigger, m_RightTrigger;

		// Private methods
		float ApplyDeadzone(float value, float maxValue, float deadZone);
		float Normalize(float input, float min, float max);
	};
}