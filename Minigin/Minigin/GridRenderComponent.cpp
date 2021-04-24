#include "MiniginPCH.h"
#include "GridRenderComponent.h"

#include <GL/gl.h>
#include <SDL.h>


#include "GridComponent.h"
#include "Renderer.h"

GridRenderComponent::GridRenderComponent(std::vector<utils::Tile> grid, Scene& scene)
	: m_Grid{grid}
{
	std::function<void()> renderWrapper = std::bind(&GridRenderComponent::Render, this);
	scene.AddRenderData(renderWrapper);
}

void GridRenderComponent::Update(float , GameObject& object)
{
	// DEBUG CODE --------------------------------------------------------------
	auto grid = object.GetComponent<GridComponent>()->GetVertices();
	m_Grid = grid;
	// -------------------------------------------------------------------------
}

void GridRenderComponent::Render() const
{
	for (auto& hexagon : m_Grid)
	{
		if(!hexagon.isActive)
			SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), 255, 0, 0, 255);
		else
			SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), 0, 255, 0, 255);
		utils::DrawHexagon(Renderer::GetInstance().GetSDLRenderer(), hexagon.vertices);
	}
}