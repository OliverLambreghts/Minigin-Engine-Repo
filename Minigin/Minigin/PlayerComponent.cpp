#include "MiniginPCH.h"
#include "PlayerComponent.h"

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