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
		m_Subject.Notify(obj, Message::PlayerDied);
		break;
	}
}

void HealthComponent::Update(float, GameObject& obj)
{
	if(m_CanDie)
	{
		Die(obj);
		m_CanDie = false;
	}
}

Subject& HealthComponent::GetSubject()
{
	return m_Subject;
}

void HealthComponent::SetCanDie()
{
	m_CanDie = true;
}