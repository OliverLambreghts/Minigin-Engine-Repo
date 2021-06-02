#pragma once
#include "CatchSamSlickCommand.h"
#include "HexTransformComponent.h"

class SlickSamTransformComponent final : public HexTransformComponent
{
public:
	enum class EntityType
	{
		slick,
		sam
	};

	SlickSamTransformComponent(std::shared_ptr<std::vector<utils::Tile*>>& grid, std::function<std::pair<int, int>()> getQbertPos,
		EntityType type, std::shared_ptr<CatchSamSlickCommand> killCmd,
		std::function<std::pair<int, int>()> getQbertPos2);
	virtual ~SlickSamTransformComponent() = default;
	SlickSamTransformComponent(const SlickSamTransformComponent& other) = delete;
	SlickSamTransformComponent(SlickSamTransformComponent&& other) = delete;
	void operator=(const SlickSamTransformComponent& rhs) = delete;
	void operator=(const SlickSamTransformComponent&& rhs) = delete;

	virtual void Update(float elapsedSec, GameObject& obj) override;

	void Reset();
private:
	void UpdatePosition(GameObject& obj);
	void AIMove();
	void HandleQBertCollision(GameObject& obj);
	void HandleFalling(GameObject& obj);
	
	EntityType m_Type;
	float m_Timer;
	bool m_IsActive;
	float m_SpawnThreshold;
	std::function<std::pair<int, int>()> m_QBertPos, m_QBertPos2;
	std::shared_ptr<CatchSamSlickCommand> m_pKillCMD;
};
