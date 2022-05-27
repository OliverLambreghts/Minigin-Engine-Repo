#include "MiniginPCH.h"
#include "CoilyTransformComponent.h"

#include <SDL.h>


#include "GraphicsComponent2D.h"
#include "InvisibleState.h"
#include "ServiceLocator.h"
#include "SnakeState.h"

CoilyTransformComponent::CoilyTransformComponent(std::shared_ptr<std::vector<utils::Tile*>>& grid, std::function<std::pair<int, int>()> getQbertPos,
	std::function<void()> killFcn, std::shared_ptr<CoilyDefeatedDiscCommand> cmd,
	std::function<std::pair<int, int>()> getQbertPos2,
	std::function<void()> killFcn2,
	bool isPlayer)
	: HexTransformComponent(grid),
	m_QBertPos{ getQbertPos },
	m_pState{ std::make_shared<InvisibleState>() },
	m_SnakeOffsetX{ 5.f },
	m_SnakeOffsetY{ 45.f },
	m_KillQBert{ killFcn },
	m_pKillCMD{ cmd },
	m_KillQBert2{ killFcn2 },
	m_QBertPos2{ getQbertPos2 },
	m_IsPlayer{ isPlayer },
	m_IsPlayerControlling{ false }
{
	Move(static_cast<Direction>(rand() % 2 + 2));
}

void CoilyTransformComponent::Update(float elapsedSec, GameObject& obj)
{
	m_Timer += elapsedSec;
	const float delayOffset = 0.25f;
	if (m_IsPlayerControlling && m_Timer < m_MoveDelay + delayOffset)
		return;
	if(m_IsPlayerControlling)
		m_Timer = 0.f;
	
	UpdatePosition(obj);

	const auto pNewState = m_pState->Update(elapsedSec, obj);
	if (pNewState)
	{
		m_pState.reset();
		m_pState = pNewState;
	}
}

void CoilyTransformComponent::UpdatePosition(GameObject& obj)
{
	CheckQBertCollision();

	// Update position
	if (m_NeedsUpdate)
	{
		HandleFalling(obj);

		if (std::dynamic_pointer_cast<SnakeState>(m_pState))
		{
			const auto newPos = m_GridMap[std::make_pair(m_Row, m_Col)]->center;
			m_Transform.SetPosition(newPos.x - m_OffsetX - m_SnakeOffsetX, newPos.y - m_OffsetY - m_SnakeOffsetY, 0.f);
			m_NeedsUpdate = false;
			return;
		}
		const auto defaultPos = m_GridMap[std::make_pair(m_Row, m_Col)]->center;
		m_Transform.SetPosition(defaultPos.x - m_OffsetX, defaultPos.y - m_OffsetY, 0.f);
		m_NeedsUpdate = false;
	}
}

void CoilyTransformComponent::HandleFalling(GameObject& obj)
{
	// Reset if Coily falls off the map
	if (m_GridMap.find(std::make_pair(m_Row, m_Col)) == m_GridMap.end())
	{
		obj.GetComponent<GraphicsComponent2D>()->SetVisibility(false);
		obj.GetComponent<GraphicsComponent2D>()->ChangeTexture("../Data/QBert/Enemies/Coily/Egg.png");
		Reset();
		// APPLY COILY BONUS HERE
		m_pKillCMD->Execute();
		ServiceLocator::GetAudioService()->PlaySound("../Data/QBert/Sounds/coilyfall.wav", SDL_MIX_MAXVOLUME);
	}
	else if (!std::dynamic_pointer_cast<InvisibleState>(m_pState))
		ServiceLocator::GetAudioService()->PlaySound("../Data/QBert/Sounds/coilyjump.wav", SDL_MIX_MAXVOLUME);
}

void CoilyTransformComponent::CheckQBertCollision()
{
	if (m_GridMap.find(std::make_pair(m_Row, m_Col)) == m_GridMap.end())
		return;
	
	// Check if Coily is on the same tile as QBert
	if (GetRowCol(true) == GetRowCol(false) && !std::dynamic_pointer_cast<InvisibleState>(m_pState))
	{
		m_KillQBert();
		ServiceLocator::GetAudioService()->PlaySound("../Data/QBert/Sounds/eaten.wav", SDL_MIX_MAXVOLUME);
	}
	else if (m_QBertPos2 && m_QBertPos2() == std::pair<int, int>(m_Row, m_Col) && !std::dynamic_pointer_cast<InvisibleState>(m_pState))
	{
		m_KillQBert2();
		ServiceLocator::GetAudioService()->PlaySound("../Data/QBert/Sounds/eaten.wav", SDL_MIX_MAXVOLUME);
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
	m_IsPlayerControlling = false;
	Move(static_cast<Direction>(rand() % 2 + 2));
}

const bool CoilyTransformComponent::IsPlayer() const
{
	return m_IsPlayer;
}

void CoilyTransformComponent::ActivatePlayerMovement()
{
	m_IsPlayerControlling = true;
}

const bool CoilyTransformComponent::IsPlayerControlling() const
{
	return m_IsPlayerControlling;
}