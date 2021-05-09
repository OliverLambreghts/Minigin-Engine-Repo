#include "MiniginPCH.h"
#include "UggWrongwayTransformComponent.h"

#include "GraphicsComponent2D.h"

UggWrongWayTransformComponent::UggWrongWayTransformComponent(std::shared_ptr<std::vector<utils::Tile1>>& grid,
	std::function<std::pair<int, int>()> getQbertPos, std::function<void()> killFcn, EntityType type)
	: HexTransformComponent(grid),
	m_Type{ type },
	m_KillQBert{ killFcn },
	m_QBertPos{ getQbertPos },
	m_IsActive{ false },
	m_WrongwayOffsetX{ 30.f },
	m_BothOffsetY{ 40.f },
	m_Timer{},
	m_SpawnThreshold{ float(rand() % 5 + 5) },
	m_UggOffsetX{ 25.f }
{
	InitPos(type);
}

void UggWrongWayTransformComponent::InitPos(EntityType type)
{
	switch (type)
	{
	case EntityType::ugg:
		m_Row = 6;
		m_Col = 0;
		break;
	case EntityType::wrongway:
		m_Row = 6;
		m_Col = -6;
		break;
	}
	m_NeedsUpdate = true;
}

void UggWrongWayTransformComponent::Update(float elapsedSec, GameObject& obj)
{
	UpdatePosition(obj);

	m_Timer += elapsedSec;

	if (!m_IsActive)
	{
		if (m_Timer >= m_SpawnThreshold)
		{
			m_IsActive = true;
			obj.GetComponent<GraphicsComponent2D>()->SetVisibility(true);
			m_Timer = 0.f;
		}
		return;
	}

	HandleQBertCollision();
	AIMove();
}

void UggWrongWayTransformComponent::HandleQBertCollision()
{
	// Kill Qbert when he's on the left lower tile next to wrong or right lower tile next to ugg
	switch (m_Type)
	{
	case EntityType::ugg:
		if (m_QBertPos().first == m_Row + 1 && m_QBertPos().second == m_Col)
			m_KillQBert();
		break;
	case EntityType::wrongway:
		if (m_QBertPos().first == m_Row + 1 && m_QBertPos().second == m_Col - 1)
			m_KillQBert();
		break;
	}
}

void UggWrongWayTransformComponent::AIMove()
{
	if (m_Timer >= 1.f)
	{
		Direction uggMoves[2]{ Direction::downLeft, Direction::topLeft };
		Direction wWMoves[2]{ Direction::downRight, Direction::topRight };
		switch (m_Type)
		{
		case EntityType::ugg:
			if (m_Row < 6)
				Move(uggMoves[rand() % 2]);
			else
				Move(Direction::topLeft);
			break;
		case EntityType::wrongway:
			if (m_Row < 6)
				Move(wWMoves[rand() % 2]);
			else
				Move(Direction::topRight);
			break;
		}
		m_Timer = 0.f;
	}
}

void UggWrongWayTransformComponent::UpdatePosition(GameObject& obj)
{
	if (!m_NeedsUpdate)
		return;


	// Reset when out of bounds
	if (m_Grid.find(std::make_pair(m_Row, m_Col)) == m_Grid.end())
	{
		obj.GetComponent<GraphicsComponent2D>()->SetVisibility(false);
		Reset();
	}

	auto newPos = m_Grid[std::make_pair(m_Row, m_Col)]->center;
	switch (m_Type)
	{
	case EntityType::ugg:
		m_Transform.SetPosition(newPos.x - m_OffsetX + m_UggOffsetX, newPos.y - m_OffsetY + m_BothOffsetY, 0.f);
		m_NeedsUpdate = false;
		break;
	case EntityType::wrongway:
		m_Transform.SetPosition(newPos.x - m_OffsetX - m_WrongwayOffsetX, newPos.y - m_OffsetY + m_BothOffsetY, 0.f);
		m_NeedsUpdate = false;
		break;
	}
}

void UggWrongWayTransformComponent::Reset()
{
	switch (m_Type)
	{
	case EntityType::ugg:
		InitPos(EntityType::ugg);
		break;
	case EntityType::wrongway:
		InitPos(EntityType::wrongway);
		break;
	}
	m_Timer = 0.f;
	m_IsActive = false;
}