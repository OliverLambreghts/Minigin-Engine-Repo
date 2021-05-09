#pragma once
#include "HexTransformComponent.h"

class UggWrongWayTransformComponent: public HexTransformComponent
{
public:
	enum class EntityType
	{
		ugg,
		wrongway
	};

	void InitPos(EntityType type);
	
	UggWrongWayTransformComponent(std::shared_ptr<std::vector<utils::Tile1>>& grid, std::function<std::pair<int, int>()> getQbertPos,
		std::function<void()> killFcn, EntityType type);
	virtual ~UggWrongWayTransformComponent() = default;
	UggWrongWayTransformComponent(const UggWrongWayTransformComponent& other) = delete;
	UggWrongWayTransformComponent(UggWrongWayTransformComponent&& other) = delete;
	void operator=(const UggWrongWayTransformComponent& rhs) = delete;
	void operator=(const UggWrongWayTransformComponent&& rhs) = delete;

	virtual void Update(float elapsedSec, GameObject & obj) override;
	void UpdatePosition(GameObject& obj);
	void HandleQBertCollision();

	void AIMove();
	
	void Reset();
private:
	EntityType m_Type;
	std::function<void()> m_KillQBert;
	std::function<std::pair<int, int>()> m_QBertPos;
	bool m_IsActive;
	const float m_WrongwayOffsetX, m_BothOffsetY, m_UggOffsetX;
	float m_Timer;
	const float m_SpawnThreshold;
};
