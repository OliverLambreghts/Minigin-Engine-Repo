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
		comp.second->Update(elapsedSec, *this);
	}
}

const std::shared_ptr<Component> GameObject::GetComponent(std::string name) const
{
	return m_pComponents.at(name);
}

unsigned int GameObject::GetId()
{
	return m_IdCounter;
}

void GameObject::SetPos(float x, float y)
{
	if (m_pComponents["movement"] == nullptr)
		m_pComponents["movement"] = std::make_shared<TransformComponent>(x, y);
	else
		std::dynamic_pointer_cast<TransformComponent>(m_pComponents.at("transform"))->SetPos(x, y);
}

void GameObject::AddComponent(std::string name, std::shared_ptr<Component> comp)
{
	m_pComponents[name] = comp;
}