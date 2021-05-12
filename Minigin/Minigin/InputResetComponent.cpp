#include "MiniginPCH.h"
#include "InputResetComponent.h"

InputResetComponent::InputResetComponent(const Scene& scene)
	: m_HasAddedCMDS{ false },
	m_Scene{ scene }
{
}

void InputResetComponent::Update(float, dae::GameObject&)
{
	if (m_Scene.IsActive() && !m_HasAddedCMDS)
	{
		InputManager::GetInstance().AddCommands(m_KeyboardCommands);
		InputManager::GetInstance().AddCommands(m_ControllerCommands);
		m_HasAddedCMDS = true;
	}
}