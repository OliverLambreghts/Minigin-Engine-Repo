#include "MiniginPCH.h"
#include "EggState.h"

#include "CoilyTransformComponent.h"
#include "GraphicsComponent2D.h"
#include "InputManager.h"
#include "MoveDownLeftCommand.h"
#include "MoveDownRightCommand.h"
#include "MoveTopLeftCommand.h"
#include "MoveTopRightCommand.h"
#include "SnakeState.h"


std::shared_ptr<EnemyState> EggState::Update(float elapsedSec, dae::GameObject& obj)
{
	m_Timer += elapsedSec;
	
	if (m_Timer < 1.f)
		return nullptr;
	obj.GetComponent<CoilyTransformComponent>()->Move(static_cast<CoilyTransformComponent::Direction>(rand() % 2 + 2));
	m_Timer = 0.f;
	// Change to snake texture
	const auto rowCol = obj.GetComponent<CoilyTransformComponent>()->GetRowCol(false);
	
	if (rowCol.first == 6)
	{
		if(obj.GetComponent<CoilyTransformComponent>()->IsPlayer())
			obj.GetComponent<CoilyTransformComponent>()->ActivatePlayerMovement();
		
		obj.GetComponent<GraphicsComponent2D>()->ChangeTexture("../Data/QBert/Enemies/Coily/Snake.png");
		return std::make_shared<SnakeState>();
	}
	return nullptr;
}
