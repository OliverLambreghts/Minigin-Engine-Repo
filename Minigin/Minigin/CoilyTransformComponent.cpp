#include "MiniginPCH.h"
#include "CoilyTransformComponent.h"

#include "GraphicsComponent2D.h"
#include "InvisibleState.h"
#include "SnakeState.h"

CoilyTransformComponent::CoilyTransformComponent(std::shared_ptr<std::vector<utils::Tile>>& grid, std::function<std::pair<int, int>()> getQbertPos,
	std::function<void()> dieFcn)
	: HexTransformComponent(grid),
	m_QBertPos{ getQbertPos },
	m_pState{ std::make_shared<InvisibleState>() },
	m_SnakeOffsetX{ 5.f },
	m_SnakeOffsetY{ 45.f },
	m_KillQBert{dieFcn}
{
	Move((Direction)(rand() % 2 + 2));
}

void CoilyTransformComponent::Update(float elapsedSec, GameObject& obj)
{
	UpdatePosition();

	auto pNewState = m_pState->Update(elapsedSec, obj);
	if (pNewState)
	{
		m_pState.reset();
		m_pState = pNewState;
	}
}

void CoilyTransformComponent::UpdatePosition()
{
	// Check if Coily is on the same tile as QBert
	if (GetRowCol(true) == GetRowCol(false) && !std::dynamic_pointer_cast<InvisibleState>(m_pState))
	{
		m_KillQBert();
	}
	
	// Update position
	if (m_NeedsUpdate)
	{
		if (std::dynamic_pointer_cast<SnakeState>(m_pState))
		{
			auto newPos = m_Grid[std::make_pair(m_Row, m_Col)]->center;
			m_Transform.SetPosition(newPos.x - m_OffsetX - m_SnakeOffsetX, newPos.y - m_OffsetY - m_SnakeOffsetY, 0.f);
			m_NeedsUpdate = false;
			return;
		}
		auto defaultPos = m_Grid[std::make_pair(m_Row, m_Col)]->center;
		m_Transform.SetPosition(defaultPos.x - m_OffsetX, defaultPos.y - m_OffsetY, 0.f);
		m_NeedsUpdate = false;
	}
}

std::pair<int, int> CoilyTransformComponent::GetRowCol(bool fromQBert)
{
	if (!fromQBert)
	{
		auto rowCol = std::make_pair(m_Row, m_Col);
		return rowCol;
	}
	return m_QBertPos();
}

void CoilyTransformComponent::Reset()
{
	m_Row = 0;
	m_Col = 0;
	m_pState.reset();
	m_pState = std::make_shared<InvisibleState>();
	Move((Direction)(rand() % 2 + 2));
}