#include "MiniginPCH.h"
#include "SlickSamTransformComponent.h"

#include <SDL.h>

#include "GraphicsComponent2D.h"
#include "ServiceLocator.h"

SlickSamTransformComponent::SlickSamTransformComponent(std::shared_ptr<std::vector<utils::Tile*>>& grid, std::function<std::pair<int, int>()> getQbertPos,
	EntityType type, std::shared_ptr<CatchSamSlickCommand> killCmd,
	std::function<std::pair<int, int>()> getQbertPos2)
	: HexTransformComponent(grid),
	m_Type{ type },
	m_Timer{},
	m_IsActive{},
	m_SpawnThreshold{ static_cast<float>(rand() % 2 + 10) },
	m_QBertPos{ getQbertPos },
	m_pKillCMD{ killCmd },
	m_QBertPos2{ getQbertPos2 }
{
	switch (type)
	{
	case EntityType::sam:
		Move(Direction::downLeft);
		break;
	case EntityType::slick:
		Move(Direction::downRight);
		break;
	}
}

void SlickSamTransformComponent::Update(float elapsedSec, GameObject& obj)
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

	HandleQBertCollision(obj);
	AIMove();
}

void SlickSamTransformComponent::HandleQBertCollision(GameObject& obj)
{
	if (m_QBertPos() == std::pair<int, int>(m_Row, m_Col) || (m_QBertPos2 && m_QBertPos2() == std::pair<int, int>(m_Row, m_Col)))
	{
		obj.GetComponent<GraphicsComponent2D>()->SetVisibility(false);
		Reset();
		m_pKillCMD->Execute();
	}
}

void SlickSamTransformComponent::UpdatePosition(GameObject& obj)
{
	if (!m_NeedsUpdate)
		return;

	HandleFalling(obj);

	const auto defaultPos = m_GridMap[std::make_pair(m_Row, m_Col)]->center;
	m_Transform.SetPosition(defaultPos.x - m_OffsetX, defaultPos.y - m_OffsetY, 0.f);
	m_NeedsUpdate = false;

	// Revert tile state
	if (m_IsActive)
		m_GridMap[std::pair<int, int>{m_Row, m_Col}]->SSInteract();
}

void SlickSamTransformComponent::HandleFalling(GameObject& obj)
{
	if (m_GridMap.find(std::make_pair(m_Row, m_Col)) == m_GridMap.end())
	{
		obj.GetComponent<GraphicsComponent2D>()->SetVisibility(false);
		Reset();
	}
	else if (m_IsActive)
		ServiceLocator::GetAudioService()->PlaySound("../Data/QBert/Sounds/otherjump.wav", SDL_MIX_MAXVOLUME);
}

void SlickSamTransformComponent::AIMove()
{
	if (m_Timer < 1.f)
		return;

	m_Timer = 0.f;
	Move(static_cast<Direction>(rand() % 2 + 2));
}

void SlickSamTransformComponent::Reset()
{
	switch (m_Type)
	{
	case EntityType::sam:
		m_Row = 1;
		m_Col = -1;
		break;
	case EntityType::slick:
		m_Row = 1;
		m_Col = 0;
		break;
	}

	m_Timer = 0.f;
	m_IsActive = false;
	m_NeedsUpdate = true;
}