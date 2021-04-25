#pragma once
#include "GameObject.h"
#include "TransformComponent.h"
#include "utils.h"

using namespace dae;
class QBertTransformComponent : public TransformComponent
{
public:
	enum class Direction
	{
		topLeft,
		topRight,
		downLeft,
		downRight
	};

	QBertTransformComponent(std::vector<utils::Tile>& grid);
	virtual ~QBertTransformComponent() = default;
	QBertTransformComponent(const QBertTransformComponent& other) = delete;
	QBertTransformComponent(QBertTransformComponent&& other) = delete;
	void operator=(const QBertTransformComponent& rhs) = delete;
	void operator=(const QBertTransformComponent&& rhs) = delete;

	virtual void Update(float elapsedSec, GameObject& obj) override;
	void Move(Direction direction);
private:
	//std::vector<utils::Tile> m_Grid;
	std::map<std::pair<int, int>, utils::Tile*> m_Grid;
	const float m_OffsetX{ 12.5f }, m_OffsetY{ 45.f };
	int m_Row, m_Col;
	bool m_NeedsUpdate;
};