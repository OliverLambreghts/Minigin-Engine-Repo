#include "MiniginPCH.h"
#include "CoilyTransformComponent.h"

#include "GraphicsComponent2D.h"
#include "InvisibleState.h"
#include "SnakeState.h"

CoilyTransformComponent::CoilyTransformComponent(std::shared_ptr<std::vector<utils::Tile*>>& grid, std::function<std::pair<int, int>()> getQbertPos,
	std::function<void()> killFcn, std::shared_ptr<CoilyDefeatedDiscCommand> cmd,
	std::function<std::pair<int, int>()> getQbertPos2,
	std::function<void()> killFcn2)
	: HexTransformComponent(grid),
	m_QBertPos{ getQbertPos },
	m_pState{ std::make_shared<InvisibleState>() },
	m_SnakeOffsetX{ 5.f },
	m_SnakeOffsetY{ 45.f },
	m_KillQBert{ killFcn },
	m_pKillCMD{ cmd },
	m_KillQBert2{ killFcn2 },
	m_QBertPos2{ getQbertPos2 }
{
	Move((Direction)(rand() % 2 + 2));
}

void CoilyTransformComponent::Update(float elapsedSec, GameObject& obj)
{
	UpdatePosition(obj);

	auto pNewState = m_pState->Update(elapsedSec, obj);
	if (pNewState)
	{
		m_pState.reset();
		m_pState = pNewState;
	}
}

void CoilyTransformComponent::UpdatePosition(GameObject& obj)
{
	// Check if Coily is on the same tile as QBert
	if (GetRowCol(true) == GetRowCol(false) && !std::dynamic_pointer_cast<InvisibleState>(m_pState))
	{
		m_KillQBert();
	}
	else if(m_QBertPos2 && m_QBertPos2() == std::pair<int, int>(m_Row, m_Col) && !std::dynamic_pointer_cast<InvisibleState>(m_pState))
	{
		m_KillQBert2();
	}

	// Update position
	if (m_NeedsUpdate)
	{
		// Reset if Coily falls off the map
		if (m_GridMap.find(std::make_pair(m_Row, m_Col)) == m_GridMap.end())
		{
			obj.GetComponent<GraphicsComponent2D>()->SetVisibility(false);
			obj.GetComponent<GraphicsComponent2D>()->ChangeTexture("../Data/QBert/Enemies/Coily/Egg.png");
			Reset();
			// APPLY COILY BONUS HERE
			m_pKillCMD->Execute();
		}

		if (std::dynamic_pointer_cast<SnakeState>(m_pState))
		{
			auto newPos = m_GridMap[std::make_pair(m_Row, m_Col)]->center;
			m_Transform.SetPosition(newPos.x - m_OffsetX - m_SnakeOffsetX, newPos.y - m_OffsetY - m_SnakeOffsetY, 0.f);
			m_NeedsUpdate = false;
			return;
		}
		auto defaultPos = m_GridMap[std::make_pair(m_Row, m_Col)]->center;
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