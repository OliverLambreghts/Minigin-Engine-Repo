#pragma once
#include "HexTransformComponent.h"

class CoilyTransformComponent : public HexTransformComponent
{
public:
	enum class State
	{
		Invisible,
		Egg,
		Snake
	};
	
	CoilyTransformComponent(std::vector<utils::Tile>& grid, std::function<std::pair<int, int>()> getQbertPos);
	virtual ~CoilyTransformComponent() = default;
	CoilyTransformComponent(const CoilyTransformComponent& other) = delete;
	CoilyTransformComponent(CoilyTransformComponent&& other) = delete;
	void operator=(const CoilyTransformComponent& rhs) = delete;
	void operator=(const CoilyTransformComponent&& rhs) = delete;

	virtual void Update(float elapsedSec, GameObject & obj) override;
	void UpdatePosition();
	void AIMove(GameObject& obj);
private:
	float m_SpawnThreshold;
	std::function<std::pair<int, int>()> m_QBertPos;
	State m_State;
};
