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
	for(auto& update : m_UpdateData)
	{
		update(elapsedSec, *this);
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
	if (m_pComponents["transform"] == nullptr)
		m_pComponents["transform"] = std::make_shared<TransformComponent>(x, y, *this);
	else
		std::dynamic_pointer_cast<TransformComponent>(m_pComponents.at("transform"))->SetPos(x, y);
}

void GameObject::AddComponent(std::string name, std::shared_ptr<Component> comp)
{
	m_pComponents[name] = comp;
}

void GameObject::AddUpdateData(std::function<void(float, GameObject&)> fcnPtr)
{
	m_UpdateData.push_back(fcnPtr);
}