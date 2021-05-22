#include "MiniginPCH.h"
#include "HealthComponent.h"

#include "SceneManager.h"

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
		--m_Lives;
		m_Subject.Notify(obj, Message::PlayerDied);
		break;
	}
}

void HealthComponent::Update(float, GameObject& obj)
{
	if (m_Lives == 0)
		SceneManager::GetInstance().MarkForDeletion();
	
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

void HealthComponent::Kill()
{
	m_CanDie = true;
}