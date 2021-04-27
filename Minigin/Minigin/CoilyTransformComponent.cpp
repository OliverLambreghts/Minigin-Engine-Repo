#include "MiniginPCH.h"
#include "CoilyTransformComponent.h"

#include "GraphicsComponent2D.h"

CoilyTransformComponent::CoilyTransformComponent(std::vector<utils::Tile>& grid, std::function<std::pair<int, int>()> getQbertPos)
	: HexTransformComponent(grid),
	m_SpawnThreshold{},
	m_QBertPos{ getQbertPos },
	m_State{ State::Invisible }
{
	Move((Direction)(rand() % 2 + 2));
	const int randomNr = rand() % 5 + 5;
	m_SpawnThreshold = float(randomNr);
}

void CoilyTransformComponent::Update(float elapsedSec, GameObject& obj)
{
	UpdatePosition();
	
	m_Timer += elapsedSec;
	if (m_State == State::Invisible && m_Timer < m_SpawnThreshold)
		return;

	AIMove(obj);
}

void CoilyTransformComponent::UpdatePosition()
{
	// Update position
	if (m_NeedsUpdate)
	{
		switch (m_State)
		{
		case State::Snake:
			auto newPos = m_Grid[std::make_pair(m_Row, m_Col)]->center;
			m_Transform.SetPosition(newPos.x - m_OffsetX - 5.f, newPos.y - m_OffsetY - 45.f, 0.f);
			m_NeedsUpdate = false;
			break;
		default:
			auto defaultPos = m_Grid[std::make_pair(m_Row, m_Col)]->center;
			m_Transform.SetPosition(defaultPos.x - m_OffsetX, defaultPos.y - m_OffsetY, 0.f);
			m_NeedsUpdate = false;
			break;
		}
	}
}

void CoilyTransformComponent::AIMove(GameObject& obj)
{
	switch (m_State)
	{
	case State::Invisible:
		m_State = State::Egg;
		obj.GetComponent<GraphicsComponent2D>()->SetVisibility(true);
		m_Timer = 0.f;
		break;
	case State::Egg:
		if (m_Timer < 1.f)
			break;
		Move((Direction)(rand() % 2 + 2));
		m_Timer = 0.f;
		// Change to snake texture
		if (m_Row == 6)
		{
			m_State = State::Snake;
			obj.GetComponent<GraphicsComponent2D>()->ChangeTexture("../Data/QBert/Enemies/Coily/Snake.png");
		}
		break;
	case State::Snake:
		if (m_Timer < 1.f)
			break;
		
		int qBertRow = m_QBertPos().first;
		int qBertCol = m_QBertPos().second;

		if (m_Row == qBertRow && m_Col == qBertCol)
			return;
		
		if (m_Row >= qBertRow && m_Col < qBertCol)
		{
			// Topright
			--m_Row;
			++m_Col;
		}
		else if (m_Row >= qBertRow && m_Col >= qBertCol)
		{
			// TopLeft
			--m_Row;
		}
		else if(m_Row <= qBertRow && m_Col <= qBertCol)
		{
			// Downright
			++m_Row;
		}
		else if(m_Row <= qBertRow && m_Col > qBertCol)
		{
			// Downleft
			++m_Row;
			--m_Col;
		}
		

		m_NeedsUpdate = true;

		m_Timer = 0.f;
		break;
	}
}