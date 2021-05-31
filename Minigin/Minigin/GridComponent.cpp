#include "MiniginPCH.h"
#include "GridComponent.h"
#include <algorithm>
#include <SDL.h>

#include "SceneManager.h"
#include "ServiceLocator.h"

GridComponent::GridComponent(float hexSize, int hexAmount, int windowWidth, std::shared_ptr<std::vector<utils::Tile*>>& grid, int level)
	: m_HexSize{ hexSize },
	m_HexAmount{ hexAmount },
	m_pTiles{ grid },
	m_IsLevelComplete{ false },
	m_EndTimer{},
	m_WindowWidth{ windowWidth }
{
	utils::Point2f center{ (float)windowWidth / 2, 75.f };
	float width = float(sqrt(3)) * hexSize;
	float height = 2 * hexSize;

	switch (level)
	{
	case 1:
		for (int amountThisRow{ 1 }; amountThisRow < hexAmount + 1; ++amountThisRow)
		{
			utils::Point2f centerThisRow{ center };
			for (int currentAmount{}; currentAmount < amountThisRow; ++currentAmount)
			{
				utils::Tile1* hexagon{ new utils::Tile1{} };
				for (int i{}; i < 6; ++i)
				{
					float angle_deg = 60.f * float(i) - 30.f;
					float angle_rad = float(M_PI) / 180.f * angle_deg;
					utils::Point2f tempPoint{ centerThisRow.x + hexSize * cos(angle_rad),
							centerThisRow.y + hexSize * sin(angle_rad) };
					hexagon->vertices.push_back(tempPoint);
					hexagon->center = centerThisRow;
				}
				centerThisRow.x += width;
				m_pTiles->push_back(hexagon);
			}
			center.y += (height * (3.f / 4.f));
			center.x -= width / 2.f;
		}
		break;
	case 2:
		for (int amountThisRow{ 1 }; amountThisRow < hexAmount + 1; ++amountThisRow)
		{
			utils::Point2f centerThisRow{ center };
			for (int currentAmount{}; currentAmount < amountThisRow; ++currentAmount)
			{
				utils::Tile2* hexagon{ new utils::Tile2{} };
				for (int i{}; i < 6; ++i)
				{
					float angle_deg = 60.f * float(i) - 30.f;
					float angle_rad = float(M_PI) / 180.f * angle_deg;
					utils::Point2f tempPoint{ centerThisRow.x + hexSize * cos(angle_rad),
							centerThisRow.y + hexSize * sin(angle_rad) };
					hexagon->vertices.push_back(tempPoint);
					hexagon->center = centerThisRow;
				}
				centerThisRow.x += width;
				m_pTiles->push_back(hexagon);
			}
			center.y += (height * (3.f / 4.f));
			center.x -= width / 2.f;
		}
		break;
	case 3:
		for (int amountThisRow{ 1 }; amountThisRow < hexAmount + 1; ++amountThisRow)
		{
			utils::Point2f centerThisRow{ center };
			for (int currentAmount{}; currentAmount < amountThisRow; ++currentAmount)
			{
				utils::Tile3* hexagon{ new utils::Tile3{} };
				for (int i{}; i < 6; ++i)
				{
					float angle_deg = 60.f * float(i) - 30.f;
					float angle_rad = float(M_PI) / 180.f * angle_deg;
					utils::Point2f tempPoint{ centerThisRow.x + hexSize * cos(angle_rad),
							centerThisRow.y + hexSize * sin(angle_rad) };
					hexagon->vertices.push_back(tempPoint);
					hexagon->center = centerThisRow;
				}
				centerThisRow.x += width;
				m_pTiles->push_back(hexagon);
			}
			center.y += (height * (3.f / 4.f));
			center.x -= width / 2.f;
		}
		break;
	}
	
}

GridComponent::~GridComponent()
{
	for (auto* tile : *m_pTiles)
	{
		delete tile;
		tile = nullptr;
	}
	m_pTiles->clear();
}

const std::vector<utils::Tile*>& GridComponent::GetVertices() const
{
	return *m_pTiles;
}

void GridComponent::Update(float elapsedSec, GameObject&)
{
	if (m_IsLevelComplete)
	{
		m_EndTimer += elapsedSec;
		if (m_EndTimer > 1.f)
			SceneManager::GetInstance().ActivateNextScene();
		return;
	}

	if (std::all_of(m_pTiles->begin(), m_pTiles->end(), [](utils::Tile* tile)
		{
			return tile->IsActive();
		}))
	{
		ServiceLocator::GetAudioService()->PlaySound("../Data/QBert/Sounds/prize.wav", SDL_MIX_MAXVOLUME);
		m_IsLevelComplete = true;
	}
}

bool GridComponent::HasLevelEnded() const
{
	return m_IsLevelComplete;
}