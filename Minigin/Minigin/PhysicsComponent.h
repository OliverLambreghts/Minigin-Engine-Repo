#pragma once
#include "GameObject.h"
#include "Component.h"

using namespace dae;
class PhysicsComponent : public Component
{
public:
	PhysicsComponent() = default;
	virtual ~PhysicsComponent() = default;
	PhysicsComponent(const PhysicsComponent& other) = delete;
	PhysicsComponent(PhysicsComponent&& other) = delete;
	void operator=(const PhysicsComponent& rhs) = delete;
	void operator=(const PhysicsComponent&& rhs) = delete;

	virtual void Update(float elapsedSec, GameObject& obj) = 0;
};