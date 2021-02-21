#pragma once
#include "GameObject.h"
#include "Component.h"

using namespace dae;
class UIComponent : public Component
{
public:
	UIComponent() = default;
	virtual ~UIComponent() = default;
	UIComponent(const UIComponent& other) = delete;
	UIComponent(UIComponent&& other) = delete;
	void operator=(const UIComponent& rhs) = delete;
	void operator=(const UIComponent&& rhs) = delete;

	virtual void Update(float elapsedSec, GameObject& obj) override = 0;

	virtual void Render() = 0;
};