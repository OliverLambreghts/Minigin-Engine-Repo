#include "MiniginPCH.h"
#include "SnakeState.h"

#include "CoilyTransformComponent.h"

std::shared_ptr<EnemyState> SnakeState::Update(float elapsedSec, dae::GameObject& obj)
{
	m_Timer += elapsedSec;
	
	if (m_Timer < 1.f)
		return nullptr;

	int qBertRow = obj.GetComponent<CoilyTransformComponent>()->GetRowCol(true).first;
	int qBertCol = obj.GetComponent<CoilyTransformComponent>()->GetRowCol(true).second;
	int row = obj.GetComponent<CoilyTransformComponent>()->GetRowCol(false).first;
	int col = obj.GetComponent<CoilyTransformComponent>()->GetRowCol(false).second;

	// When Coily catches QBert he doesn't move
	if (row == qBertRow && col == qBertCol)
		return nullptr;

	if (row >= qBertRow && col < qBertCol)
	{
		// Topright
		obj.GetComponent<CoilyTransformComponent>()->Move(CoilyTransformComponent::Direction::topRight);
		//--m_Row;
		//++m_Col;
	}
	else if (row >= qBertRow && col >= qBertCol)
	{
		// TopLeft
		obj.GetComponent<CoilyTransformComponent>()->Move(CoilyTransformComponent::Direction::topLeft);
		//--m_Row;
	}
	else if (row <= qBertRow && col <= qBertCol)
	{
		// Downright
		obj.GetComponent<CoilyTransformComponent>()->Move(CoilyTransformComponent::Direction::downRight);
		//++m_Row;
	}
	else if (row <= qBertRow && col > qBertCol)
	{
		// Downleft
		obj.GetComponent<CoilyTransformComponent>()->Move(CoilyTransformComponent::Direction::downLeft);
		//++m_Row;
		//--m_Col;
	}

	//m_NeedsUpdate = true;

	m_Timer = 0.f;
	return nullptr;
}
