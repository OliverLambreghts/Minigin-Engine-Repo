#include "MiniginPCH.h"
#include "GameObject.h"

#include "Scene.h"
#include "TransformComponent.h"

unsigned int GameObject::m_IdCounter = 0;

dae::GameObject::GameObject()
{
	++m_IdCounter;
}

dae::GameObject::~GameObject()
{
	--m_IdCounter;
}

void dae::GameObject::Update(float elapsedSec)
{
	for(auto& comp : m_pComponents)
	{
		comp->Update(elapsedSec, *this);
	}
	m_DataManager.Update();
}

unsigned int GameObject::GetId()
{
	return m_IdCounter;
}

DataManager& GameObject::GetDataManager()
{
	return m_DataManager;
}

void GameObject::AddComponent(std::shared_ptr<Component> comp)
{
	m_pComponents.push_back(comp);
}

void GameObject::SetEntity(EntityType type)
{
	m_EntityType = type;
}

EntityType GameObject::GetEntityType() const
{
	return m_EntityType;
}