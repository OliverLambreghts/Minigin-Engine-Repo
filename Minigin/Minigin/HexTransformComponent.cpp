#include "MiniginPCH.h"
#include "HexTransformComponent.h"

#include <algorithm>


#include "HealthComponent.h"
#include "ScoreComponent.h"

HexTransformComponent::HexTransformComponent(std::shared_ptr<std::vector<utils::Tile*>>& grid)
	: TransformComponent(0.f, 0.f),
	m_Row{ 0 },
	m_Col{ 0 },
	m_NeedsUpdate{ false },
	m_Timer{},
	m_OldRow{},
	m_OldCol{},
	m_CanTeleport{ false },
	m_MoveDelay{ 0.25f }
{
	auto center = grid->at(0)->center;
	m_Transform.SetPosition(center.x - m_OffsetX, center.y - m_OffsetY, 0.f);

	int idx{}, col{};
	for (int row{}; row < 7; ++row)
	{
		for (int currentCol{ col }; currentCol < 1; ++currentCol)
		{
			m_GridMap[std::make_pair(row, currentCol)] = grid->at(idx);
			++idx;
		}
		--col;
	}
}

HexTransformComponent::HexTransformComponent(std::shared_ptr<std::vector<utils::Tile*>>& grid, int row, int col)
	: TransformComponent(0.f, 0.f),
	m_Row{ row },
	m_Col{ col },
	m_NeedsUpdate{ false },
	m_Timer{},
	m_OldRow{},
	m_OldCol{},
	m_CanTeleport{ false },
	m_MoveDelay{ 0.25f }
{
	int idx{}, gridCol{};
	for (int gridRow{}; gridRow < 7; ++gridRow)
	{
		for (int currentCol{ gridCol }; currentCol < 1; ++currentCol)
		{
			m_GridMap[std::make_pair(gridRow, currentCol)] = grid->at(idx);
			++idx;
		}
		--gridCol;
	}

	auto center = m_GridMap[std::pair<int, int>(row, col)]->center;
	m_Transform.SetPosition(center.x - m_OffsetX, center.y - m_OffsetY, 0.f);
}

void HexTransformComponent::Update(float elapsedSec, GameObject& obj)
{
	if (!m_NeedsUpdate)
		return;

	m_Timer += elapsedSec;
	if (m_Timer < m_MoveDelay)
		return;

	m_Timer = 0.f;

	if (HandleOutOfBounds(obj))
		return;
	
	ActivateTile(obj);

	UpdatePosition();
}

void HexTransformComponent::UpdatePosition()
{
	auto newPos = m_GridMap[std::make_pair(m_Row, m_Col)]->center;
	m_Transform.SetPosition(newPos.x - m_OffsetX, newPos.y - m_OffsetY, 0.f);
	m_NeedsUpdate = false;
	// Double buffer-ish swap: 2 Cols and Rows, 1 for reading, 1 for writing.
	m_OldRow = m_Row;
	m_OldCol = m_Col;
}

void HexTransformComponent::ActivateTile(GameObject& obj)
{
	// Activate tile
	if (!m_GridMap[std::make_pair(m_Row, m_Col)]->IsActive())
	{
		m_GridMap[std::make_pair(m_Row, m_Col)]->QBInteract();
		obj.GetComponent<ScoreComponent>()->SetScoreEvent(Message::ColorChange);
	}
	else if (dynamic_cast<utils::Tile3*>(m_GridMap[std::make_pair(m_Row, m_Col)]))
	{
		m_GridMap[std::make_pair(m_Row, m_Col)]->QBInteract();
	}
}

bool HexTransformComponent::HandleOutOfBounds(GameObject& obj)
{
	// Going out of bounds
	if (m_GridMap.find(std::make_pair(m_Row, m_Col)) == m_GridMap.end())
	{
		// If out of bounds but m_CanTeleport is active means QBert jumped on a Disc
		if (m_CanTeleport)
		{
			m_OldRow = m_Row;
			m_OldCol = m_Col;
			m_Row = 0;
			m_Col = 0;
			auto newPos = m_GridMap[std::make_pair(m_Row, m_Col)]->center;
			m_Transform.SetPosition(newPos.x - m_OffsetX, newPos.y - m_OffsetY, 0.f);
			m_NeedsUpdate = false;
			// Double buffer-ish swap: 2 Cols and Rows, 1 for reading, 1 for writing.
			m_CanTeleport = false;
			return true;
		}

		m_Row = 0;
		m_Col = 0;
		auto newPos = m_GridMap[std::make_pair(m_Row, m_Col)]->center;
		m_Transform.SetPosition(newPos.x - m_OffsetX, newPos.y - m_OffsetY, 0.f);
		m_NeedsUpdate = false;
		obj.GetComponent<HealthComponent>()->Die(obj);
		// Double buffer-ish swap: 2 Cols and Rows, 1 for reading, 1 for writing.
		m_OldRow = m_Row;
		m_OldCol = m_Col;
		return true;
	}
	return false;
}

void HexTransformComponent::Move(Direction direction)
{
	if (m_NeedsUpdate)
		return;
	m_NeedsUpdate = true;
	// Sets current buffer to next buffer and updates next buffer
	m_OldRow = m_Row;
	m_OldCol = m_Col;
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
	auto rowCol = std::make_pair(m_OldRow, m_OldCol);
	return rowCol;
}

void HexTransformComponent::SetTeleport(bool canTeleport)
{
	m_CanTeleport = canTeleport;
}