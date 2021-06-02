#pragma once
#include "HexTransformComponent.h"

class UggWrongWayTransformComponent final : public HexTransformComponent
{
public:
	enum class EntityType
	{
		ugg,
		wrongway
	};

	void InitPos(EntityType type);
	
	UggWrongWayTransformComponent(std::shared_ptr<std::vector<utils::Tile*>>& grid, std::function<std::pair<int, int>()> getQbertPos,
		std::function<void()> killFcn, EntityType type,
		std::function<std::pair<int, int>()> getQbertPos2,
		std::function<void()> killFcn2);
	virtual ~UggWrongWayTransformComponent() = default;
	UggWrongWayTransformComponent(const UggWrongWayTransformComponent& other) = delete;
	UggWrongWayTransformComponent(UggWrongWayTransformComponent&& other) = delete;
	void operator=(const UggWrongWayTransformComponent& rhs) = delete;
	void operator=(const UggWrongWayTransformComponent&& rhs) = delete;

	virtual void Update(float elapsedSec, GameObject & obj) override;
	
	void Reset();
private:
	void UpdatePosition(GameObject& obj);
	void HandleQBertCollision() const;
	void HandleFalling(GameObject& obj);
	void AIMove();
	
	EntityType m_Type;
	std::function<void()> m_KillQBert, m_KillQBert2;
	std::function<std::pair<int, int>()> m_QBertPos, m_QBertPos2;
	bool m_IsActive;
	const float m_WrongwayOffsetX, m_BothOffsetY, m_UggOffsetX;
	float m_Timer;
	const float m_SpawnThreshold;
};
