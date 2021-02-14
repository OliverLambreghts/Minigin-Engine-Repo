#pragma once
#include "GameObject.h"
#include "Component.h"

using namespace dae;
class GraphicsComponent : public Component
{
public:
	GraphicsComponent() = default;
	virtual ~GraphicsComponent() = default;
	GraphicsComponent(const GraphicsComponent& other) = delete;
	GraphicsComponent(GraphicsComponent&& other) = delete;
	void operator=(const GraphicsComponent& rhs) = delete;
	void operator=(const GraphicsComponent&& rhs) = delete;

	virtual void Update(float elapsedSec, GameObject& obj) = 0;
};