#include "MiniginPCH.h"
#include "HealthComponent.h"

void HealthComponent::SetHealth(int health)
{
	m_Health = health;
}

void HealthComponent::Die(const GameObject& obj)
{
	m_Health = 0;
	switch (obj.GetEntityType())
	{
	case EntityType::Player:
		//m_Subject->Notify(obj, Message::PlayerDied);
		Notify(obj, Message::PlayerDied);
		break;
	}
}

void HealthComponent::Update(float, GameObject&)
{
	
}