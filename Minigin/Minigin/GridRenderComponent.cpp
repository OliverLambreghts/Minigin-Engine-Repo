#include "MiniginPCH.h"
#include "GridRenderComponent.h"

#include <GL/gl.h>
#include <SDL.h>


#include "GridComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"

GridRenderComponent::GridRenderComponent(const std::vector<utils::Tile*>& grid, Scene& scene)
	: m_Grid{ grid },
	m_TileOffsetX{ 30.f }
{
	if (dynamic_cast<utils::Tile1*>(grid.front()))
	{
		m_Tile2 = ResourceManager::GetInstance().LoadTexture("../Data/QBert/Blocks/Level1/Active.png");
		m_Tile1 = ResourceManager::GetInstance().LoadTexture("../Data/QBert/Blocks/Level1/Inactive.png");
	}
	else if (dynamic_cast<utils::Tile2*>(grid.front()))
	{
		m_Tile2 = ResourceManager::GetInstance().LoadTexture("../Data/QBert/Blocks/Level2/2.png");
		m_Tile1 = ResourceManager::GetInstance().LoadTexture("../Data/QBert/Blocks/Level2/1.png");
		m_Tile3 = ResourceManager::GetInstance().LoadTexture("../Data/QBert/Blocks/Level2/3.png");
	}

	std::function<void()> renderWrapper = std::bind(&GridRenderComponent::Render, this);
	scene.AddRenderData(renderWrapper);
}

void GridRenderComponent::Update(float, GameObject& object)
{
	// DEBUG CODE --------------------------------------------------------------
	auto grid = object.GetComponent<GridComponent>()->GetVertices();
	m_Grid = grid;
	// -------------------------------------------------------------------------
}

void GridRenderComponent::Render() const
{
	for (auto* hexagon : m_Grid)
	{
		if (dynamic_cast<utils::Tile1*>(hexagon))
		{
			if (!hexagon->IsActive())
			{
				Renderer::GetInstance().RenderTexture(*m_Tile1, hexagon->vertices[5].x - m_TileOffsetX, hexagon->vertices[5].y);
				SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), 255, 0, 0, 255);
			}
			else
			{
				Renderer::GetInstance().RenderTexture(*m_Tile2, hexagon->vertices[5].x - m_TileOffsetX, hexagon->vertices[5].y);
				SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), 0, 255, 0, 255);
			}
		}
		else if (dynamic_cast<utils::Tile2*>(hexagon))
		{
			if (hexagon->IsActive())
				Renderer::GetInstance().RenderTexture(*m_Tile3, hexagon->vertices[5].x - m_TileOffsetX, hexagon->vertices[5].y);
			else if (dynamic_cast<utils::Tile2*>(hexagon)->isActiveOne)
				Renderer::GetInstance().RenderTexture(*m_Tile2, hexagon->vertices[5].x - m_TileOffsetX, hexagon->vertices[5].y);
			else
				Renderer::GetInstance().RenderTexture(*m_Tile1, hexagon->vertices[5].x - m_TileOffsetX, hexagon->vertices[5].y);
		}
		// DEBUG RENDERING
		//utils::DrawHexagon(Renderer::GetInstance().GetSDLRenderer(), hexagon.vertices);
	}
}