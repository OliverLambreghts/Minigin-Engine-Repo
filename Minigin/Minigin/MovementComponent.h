#pragma once
#include "GameObject.h"
#include "Component.h"

using namespace dae;
class MovementComponent : public Component
{
public:
	MovementComponent() = default;
	virtual ~MovementComponent() = default;
	MovementComponent(const MovementComponent& other) = delete;
	MovementComponent(MovementComponent&& other) = delete;
	void operator=(const MovementComponent& rhs) = delete;
	void operator=(const MovementComponent&& rhs) = delete;

	virtual void Update(float elapsedSec, GameObject& obj) = 0;
};