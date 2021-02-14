#include "MiniginPCH.h"
#include "FPSComponent.h"

FPSComponent::FPSComponent(TextComponent* comp, void (TextComponent::* fcnPtr) (std::string))
	: m_Delay{},
	m_FPS{}
{
	m_Wrapper = std::bind(fcnPtr, comp, std::placeholders::_1);
}

void FPSComponent::Update(float elapsedSec, GameObject&)
{
	m_Delay += elapsedSec;
	m_FPS = int(1 / elapsedSec);
	if (m_Delay < m_ResetPoint)
		return;
	m_Wrapper(std::to_string(m_FPS) + " FPS");
	m_Delay = 0.f;
}
