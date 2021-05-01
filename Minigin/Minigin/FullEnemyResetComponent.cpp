#include "MiniginPCH.h"
#include "FullEnemyResetComponent.h"

void FullEnemyResetComponent::Update(float , GameObject& )
{
	
}

void FullEnemyResetComponent::ResetAll()
{
	for(auto& resetFcn : m_pResetFcns)
	{
		resetFcn();
	}
}

void FullEnemyResetComponent::AddResetter(std::function<void()>& resetter)
{
	m_pResetFcns.push_back(resetter);
}