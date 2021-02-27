#include "MiniginPCH.h"
#include "PlayerComponent.h"

UINT PlayerComponent::m_CurrentID = 0;

PlayerComponent::PlayerComponent()
	: m_ID{m_CurrentID}
{
	++m_CurrentID;
}

void PlayerComponent::Update(float , GameObject& )
{
	
}

UINT PlayerComponent::GetID() const
{
	return m_ID;
}