#pragma once
#include "GameObject.h"
#include "Component.h"

using namespace dae;
class InputComponent : public Component
{
public:
	InputComponent() = default;
	virtual ~InputComponent() = default;
	InputComponent(const InputComponent& other) = delete;
	InputComponent(InputComponent&& other) = delete;
	void operator=(const InputComponent& rhs) = delete;
	void operator=(const InputComponent&& rhs) = delete;

	virtual void Update(float elapsedSec, GameObject& obj) = 0;
};