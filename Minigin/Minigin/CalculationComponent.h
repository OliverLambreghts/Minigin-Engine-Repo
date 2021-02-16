#pragma once
#include "GameObject.h"
#include "Component.h"

using namespace dae;
class CalculationComponent : public Component
{
public:
	CalculationComponent() = default;
	virtual ~CalculationComponent() = default;
	CalculationComponent(const CalculationComponent& other) = delete;
	CalculationComponent(CalculationComponent&& other) = delete;
	void operator=(const CalculationComponent& rhs) = delete;
	void operator=(const CalculationComponent&& rhs) = delete;

	virtual void Update(float elapsedSec, GameObject& obj) override = 0;
};