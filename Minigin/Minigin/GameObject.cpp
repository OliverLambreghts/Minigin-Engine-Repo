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
}

unsigned int GameObject::GetId()
{
	return m_IdCounter;
}

void GameObject::AddComponent(std::shared_ptr<Component> comp)
{
	m_pComponents.push_back(comp);
}