#include "MiniginPCH.h"
#include "HexTransformComponent.h"

#include "HealthComponent.h"

HexTransformComponent::HexTransformComponent(std::vector<utils::Tile>& grid)
	: TransformComponent(0.f, 0.f),
	m_Row{ 0 },
	m_Col{ 0 },
	m_NeedsUpdate{ false },
	m_Timer{}
{
	auto center = grid[0].center;
	m_Transform.SetPosition(center.x - m_OffsetX, center.y - m_OffsetY, 0.f);

	int idx{}, col{};
	for (int row{}; row < 7; ++row)
	{
		for (int currentCol{ col }; currentCol < 1; ++currentCol)
		{
			m_Grid[std::make_pair(row, currentCol)] = &grid[idx];
			++idx;
		}
		--col;
	}
}

void HexTransformComponent::Update(float elapsedSec, GameObject& obj)
{
	if (!m_NeedsUpdate)
		return;

	m_Timer += elapsedSec;
	if (m_Timer < 0.5f)
		return;

	m_Timer = 0.f;
	
	if (m_Grid.find(std::make_pair(m_Row, m_Col)) == m_Grid.end())
	{
		m_Row = 0;
		m_Col = 0;
		auto newPos = m_Grid[std::make_pair(m_Row, m_Col)]->center;
		m_Transform.SetPosition(newPos.x - m_OffsetX, newPos.y - m_OffsetY, 0.f);
		m_NeedsUpdate = false;
		obj.GetComponent<HealthComponent>()->Die(obj);
		return;
	}
	m_Grid[std::make_pair(m_Row, m_Col)]->isActive = true;
	auto newPos = m_Grid[std::make_pair(m_Row, m_Col)]->center;
	m_Transform.SetPosition(newPos.x - m_OffsetX, newPos.y - m_OffsetY, 0.f);
	m_NeedsUpdate = false;
}

void HexTransformComponent::Move(Direction direction)
{
	if (m_NeedsUpdate)
		return;
	m_NeedsUpdate = true;
	switch (direction)
	{
	case Direction::topLeft:
		--m_Row;
		break;
	case Direction::topRight:
		--m_Row;
		++m_Col;
		break;
	case Direction::downLeft:
		++m_Row;
		--m_Col;
		break;
	case Direction::downRight:
		++m_Row;
		break;
	}
}

std::pair<int, int> HexTransformComponent::GetRowCol()
{
	auto rowCol = std::make_pair(m_Row, m_Col);
	return rowCol;
}