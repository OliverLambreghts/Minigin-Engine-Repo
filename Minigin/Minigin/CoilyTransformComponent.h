#pragma once
#include "HexTransformComponent.h"

class EnemyState;

class CoilyTransformComponent : public HexTransformComponent
{
public:
	CoilyTransformComponent(std::shared_ptr<std::vector<utils::Tile1>>& grid, std::function<std::pair<int, int>()> getQbertPos, 
		std::function<void()> killFcn);
	virtual ~CoilyTransformComponent() = default;
	CoilyTransformComponent(const CoilyTransformComponent& other) = delete;
	CoilyTransformComponent(CoilyTransformComponent&& other) = delete;
	void operator=(const CoilyTransformComponent& rhs) = delete;
	void operator=(const CoilyTransformComponent&& rhs) = delete;

	virtual void Update(float elapsedSec, GameObject & obj) override;
	void UpdatePosition();

	std::pair<int, int> GetRowCol(bool fromQBert);

	void Reset();
private:
	std::function<std::pair<int, int>()> m_QBertPos;
	std::function<void()> m_KillQBert;
	std::shared_ptr<EnemyState> m_pState;
	const float m_SnakeOffsetX, m_SnakeOffsetY;
};
