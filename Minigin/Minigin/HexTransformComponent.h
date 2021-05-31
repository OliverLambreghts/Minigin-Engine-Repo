#pragma once
#include "GameObject.h"
#include "TransformComponent.h"
#include "utils.h"

using namespace dae;
class HexTransformComponent: public TransformComponent
{
public:	
	enum class Direction
	{
		topLeft,
		topRight,
		downLeft,
		downRight
	};

	HexTransformComponent(std::shared_ptr<std::vector<utils::Tile*>>& grid);
	HexTransformComponent(std::shared_ptr<std::vector<utils::Tile*>>& grid, int row, int col);
	virtual ~HexTransformComponent() = default;
	HexTransformComponent(const HexTransformComponent& other) = delete;
	HexTransformComponent(HexTransformComponent&& other) = delete;
	void operator=(const HexTransformComponent& rhs) = delete;
	void operator=(const HexTransformComponent&& rhs) = delete;

	virtual void Update(float elapsedSec, GameObject& obj) override;
	void Move(Direction direction);
	bool HandleOutOfBounds(GameObject& obj);
	void ActivateTile(GameObject& obj);
	void UpdatePosition();

	void SetTeleport(bool canTeleport);

	std::pair<int, int> GetRowCol();
protected:
	std::map<std::pair<int, int>, utils::Tile*> m_GridMap;
	const float m_OffsetX{ 12.5f }, m_OffsetY{ 45.f };
	int m_Row, m_Col, m_OldRow, m_OldCol;
	bool m_NeedsUpdate;
	float m_Timer;
	bool m_CanTeleport;
	const float m_MoveDelay;
};