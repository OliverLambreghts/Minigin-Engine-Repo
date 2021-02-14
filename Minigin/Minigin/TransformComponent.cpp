#include "MiniginPCH.h"
#include "TransformComponent.h"

TransformComponent::TransformComponent(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.f);
}

void TransformComponent::Update(float, GameObject&)
{
}

const Transform& TransformComponent::GetPos() const
{
	return m_Transform;
}

void TransformComponent::SetPos(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}