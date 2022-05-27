#include "MiniginPCH.h"
#include "SnakeState.h"

#include "CoilyTransformComponent.h"

std::shared_ptr<EnemyState> SnakeState::Update(float elapsedSec, dae::GameObject& obj)
{
	m_Timer += elapsedSec;
	
	if (m_Timer < 1.f)
		return nullptr;

	const int qBertRow = obj.GetComponent<CoilyTransformComponent>()->GetRowCol(true).first;
	const int qBertCol = obj.GetComponent<CoilyTransformComponent>()->GetRowCol(true).second;
	const int row = obj.GetComponent<CoilyTransformComponent>()->GetRowCol(false).first;
	const int col = obj.GetComponent<CoilyTransformComponent>()->GetRowCol(false).second;

	// When Coily catches QBert he doesn't move
	if (row == qBertRow && col == qBertCol)
		return nullptr;

	if(!obj.GetComponent<CoilyTransformComponent>()->IsPlayer())
	{
		if (row >= qBertRow && col < qBertCol)
		{
			// Topright
			obj.GetComponent<CoilyTransformComponent>()->Move(CoilyTransformComponent::Direction::topRight);
		}
		else if (row >= qBertRow && col >= qBertCol)
		{
			// TopLeft
			obj.GetComponent<CoilyTransformComponent>()->Move(CoilyTransformComponent::Direction::topLeft);
		}
		else if (row <= qBertRow && col <= qBertCol)
		{
			// Downright
			obj.GetComponent<CoilyTransformComponent>()->Move(CoilyTransformComponent::Direction::downRight);
		}
		else if (row <= qBertRow && col > qBertCol)
		{
			// Downleft
			obj.GetComponent<CoilyTransformComponent>()->Move(CoilyTransformComponent::Direction::downLeft);
		}
	}

	m_Timer = 0.f;
	return nullptr;
}
