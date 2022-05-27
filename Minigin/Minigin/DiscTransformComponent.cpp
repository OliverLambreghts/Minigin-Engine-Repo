#include "MiniginPCH.h"
#include "DiscTransformComponent.h"
#include <algorithm>
#include <SDL.h>

#include "GraphicsComponent2D.h"
#include "ServiceLocator.h"

int DiscTransformComponent::m_Counter{};

DiscTransformComponent::DiscTransformComponent(std::shared_ptr<std::vector<utils::Tile*>>& grid, std::function<std::pair<int, int>()> getQbertPos,
	std::function<void(bool)> setTP, std::function<const bool()> hasLevelEnded, std::shared_ptr<RemainingDiscCommand> discCMD, bool left,
	std::function<std::pair<int, int>()> getQbertPos2,
	std::function<void(bool)> setTP2)
	: HexTransformComponent(grid),
	m_QBertPos{ getQbertPos },
	m_SetTeleport{ setTP },
	m_IsActive{ false },
	m_HasBeenUsed{ false },
	m_DiscOffsetX{ 50.f },
	m_DiscOffsetY{ 10.f },
	m_HasLevelEnded{ hasLevelEnded },
	m_pDiscCMD{ discCMD },
	m_HasScoreChanged{ false },
	m_QBertPos2{ getQbertPos2 },
	m_SetTeleport2{ setTP2 }
{
	InitPos(left);
}

void DiscTransformComponent::InitPos(bool left)
{
	m_Row = (rand() % 6 + 1);
	switch (left)
	{
	case true:
		m_Col = -m_Row;
		const auto leftPos = m_GridMap[std::make_pair(m_Row, m_Col)]->center;
		m_Transform.SetPosition(leftPos.x - m_OffsetX - m_DiscOffsetX, leftPos.y - m_OffsetY + m_DiscOffsetY, 0.f);
		break;
	case false:
		m_Col = 0;
		const auto rightPos = m_GridMap[std::make_pair(m_Row, m_Col)]->center;
		m_Transform.SetPosition(rightPos.x - m_OffsetX + m_DiscOffsetX, rightPos.y - m_OffsetY + m_DiscOffsetY, 0.f);
		break;
	}
}

DiscTransformComponent::~DiscTransformComponent()
{
	--m_Counter;
}

void DiscTransformComponent::Update(float, GameObject& obj)
{
	HandleTeleportActivity(obj);

	if (!m_HasBeenUsed && !m_HasScoreChanged && std::all_of(m_GridMap.begin(), m_GridMap.end(), [](std::pair<std::pair<int, int>, utils::Tile*> tile) {return tile.second->IsActive(); }))
	{
		m_pDiscCMD->Execute();
		m_HasScoreChanged = true;
	}
}

void DiscTransformComponent::HandleTeleportActivity(GameObject& obj)
{
	if (m_HasBeenUsed)
		return;

	if (m_QBertPos2 && m_QBertPos2() == std::pair<int, int>(m_Row, m_Col))
	{
		// Activate QBert's teleport flag
		m_SetTeleport2(true);
		m_IsActive = true;
	}
	else if (m_QBertPos() == std::pair<int, int>(m_Row, m_Col))
	{
		// Activate QBert's teleport flag
		m_SetTeleport(true);
		m_IsActive = true;
	}
	else if (m_IsActive)
	{
		// First check if QBert is out of bounds which means he jumped on the Disc
		if (m_GridMap.find(std::pair<int, int>(m_QBertPos().first, m_QBertPos().second)) == m_GridMap.end())
		{
			ServiceLocator::GetAudioService()->PlaySound("../Data/QBert/Sounds/disc.wav", SDL_MIX_MAXVOLUME);
			m_HasBeenUsed = true;
			obj.GetComponent<GraphicsComponent2D>()->SetVisibility(false);
			return;
		}
		if (m_QBertPos2 && m_GridMap.find(std::pair<int, int>(m_QBertPos2().first, m_QBertPos2().second)) == m_GridMap.end())
		{
			ServiceLocator::GetAudioService()->PlaySound("../Data/QBert/Sounds/disc.wav", SDL_MIX_MAXVOLUME);
			m_HasBeenUsed = true;
			obj.GetComponent<GraphicsComponent2D>()->SetVisibility(false);
			return;
		}

		m_IsActive = false;
		// Deactivate QBert's teleport flag
		m_SetTeleport(false);
		if (m_SetTeleport2)
			m_SetTeleport2(false);
	}
}