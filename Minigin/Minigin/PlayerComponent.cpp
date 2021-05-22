#include "MiniginPCH.h"
#include "PlayerComponent.h"

//UINT PlayerComponent::m_CurrentID = 0;

PlayerComponent::PlayerComponent(UINT playerID)
	: m_ID{ playerID }
{

}

void PlayerComponent::Update(float, GameObject&)
{

}

UINT PlayerComponent::GetID() const
{
	return m_ID;
}