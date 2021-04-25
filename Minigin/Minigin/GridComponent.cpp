#include "MiniginPCH.h"
#include "GridComponent.h"

#include <SDL.h>

GridComponent::GridComponent(float hexSize, int hexAmount, int windowWidth)
	: m_HexSize{hexSize},
	m_HexAmount{hexAmount}
{
	utils::Point2f center{ (float)windowWidth / 2, 75.f};
	float width = float(sqrt(3)) * hexSize;
	float height = 2 * hexSize;

	for(int amountThisRow{1}; amountThisRow < hexAmount + 1; ++amountThisRow)
	{
		utils::Point2f centerThisRow{center};
		for(int currentAmount{}; currentAmount < amountThisRow; ++currentAmount)
		{
			utils::Tile hexagon{};
			for (int i{}; i < 6; ++i)
			{
				float angle_deg = 60.f * float(i) - 30.f;
				float angle_rad = float(M_PI) / 180.f * angle_deg;
				utils::Point2f tempPoint{ centerThisRow.x + hexSize * cos(angle_rad),
						centerThisRow.y + hexSize * sin(angle_rad) };
				hexagon.vertices.push_back(tempPoint);
				hexagon.center = centerThisRow;
			}
			centerThisRow.x += width;
			m_Tiles.push_back(hexagon);
		}
		center.y += (height * (3.f/4.f));
		center.x -= width / 2.f;
	}
}

std::vector<utils::Tile>& GridComponent::GetVertices()
{
	return m_Tiles;
}

void GridComponent::Update(float , GameObject& )
{
	// TIJDELIJKE DEBUG CODE ---------------------------------------
	/*SDL_Event e{};
	while (SDL_PollEvent(&e) != 0)
	{
		switch (e.type)
		{
		case SDL_MOUSEBUTTONUP:
			switch(e.button.button)
			{
			case SDL_BUTTON_LEFT:
				utils::Point2f mousePos{float(e.button.x), float(e.button.y)};
				std::cout << mousePos.x << " , " << mousePos.y << '\n';
				for (auto& tile : m_Tiles)
				{
					if (utils::IsPointInPolygon(mousePos, tile.vertices))
					{
						tile.isActive = true;
					}
				}
				break;
			}
			break;
		}
	}*/
	// ---------------------------------------------------------------
}
