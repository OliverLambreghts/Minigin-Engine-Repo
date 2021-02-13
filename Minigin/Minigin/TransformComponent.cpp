#include "MiniginPCH.h"
#include "TransformComponent.h"

TransformComponent::TransformComponent(float x, float y, GameObject& obj)
{
	m_Transform.SetPosition(x, y, 0.f);
	const std::function<void(float, GameObject&)> updateWrapper = std::bind(&TransformComponent::Update, this, std::placeholders::_1, std::placeholders::_2);
	obj.AddUpdateData(updateWrapper);
}

void TransformComponent::Update(float, GameObject&)
{
	/*if(!m_IsPosSet)
	{
		obj.SetPosition(m_Transform.GetPosition().x, m_Transform.GetPosition().y);
		m_IsPosSet = true;
	}*/
}

const Transform& TransformComponent::GetPos() const
{
	return m_Transform;
}

void TransformComponent::SetPos(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}