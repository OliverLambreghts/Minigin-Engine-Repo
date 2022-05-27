#include "MiniginPCH.h"
#include "FPSComponent.h"

FPSComponent::FPSComponent()
	: m_Delay{},
	m_FPS{},
	m_ResetPoint{ 1.f }
{
}

void FPSComponent::Update(float elapsedSec, GameObject&)
{
	m_Delay += elapsedSec;
	if (m_Delay < m_ResetPoint)
		return;
	m_FPS = static_cast<int>(1 / elapsedSec);
	m_Delay -= m_ResetPoint;
}

std::string FPSComponent::GetFPS()
{
	return (std::to_string(m_FPS) + " FPS");
}