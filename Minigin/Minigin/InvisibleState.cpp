#include "MiniginPCH.h"
#include "InvisibleState.h"

#include "EggState.h"
#include "GraphicsComponent2D.h"

InvisibleState::InvisibleState()
	: m_SpawnThreshold{},
	m_Timer{}
{
	const int randomNr = rand() % 5 + 5;
	m_SpawnThreshold = static_cast<float>(randomNr);
}

std::shared_ptr<EnemyState> InvisibleState::Update(float elapsedSec, dae::GameObject& obj)
{
	m_Timer += elapsedSec;
	if (m_Timer < m_SpawnThreshold)
		return nullptr;
	
	obj.GetComponent<GraphicsComponent2D>()->SetVisibility(true);
	m_Timer = 0.f;
	return std::make_shared<EggState>();
}