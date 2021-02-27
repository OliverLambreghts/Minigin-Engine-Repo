#pragma once
#include "GameObject.h"
#include "Component.h"

using namespace dae;
class GameplayComponent : public Component
{
public:
	GameplayComponent() = default;
	virtual ~GameplayComponent() = default;
	GameplayComponent(const GameplayComponent& other) = delete;
	GameplayComponent(GameplayComponent&& other) = delete;
	void operator=(const GameplayComponent& rhs) = delete;
	void operator=(const GameplayComponent&& rhs) = delete;

	virtual void Update(float elapsedSec, GameObject& obj) override = 0;
};