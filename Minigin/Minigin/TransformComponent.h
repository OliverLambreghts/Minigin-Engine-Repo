#pragma once
#include "GameObject.h"
#include "Component.h"
#include "Transform.h"

using namespace dae;
class TransformComponent : public Component
{
public:
	TransformComponent(float x, float y, GameObject& obj);
	virtual ~TransformComponent() = default;
	TransformComponent(const TransformComponent& other) = delete;
	TransformComponent(TransformComponent&& other) = delete;
	void operator=(const TransformComponent& rhs) = delete;
	void operator=(const TransformComponent&& rhs) = delete;

	const Transform& GetPos() const;
	void SetPos(float x, float y);
	
	virtual void Update(float elapsedSec, GameObject& obj);
private:
	bool m_IsPosSet = false;
	dae::Transform m_Transform;
};