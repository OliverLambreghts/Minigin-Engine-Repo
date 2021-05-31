#pragma once
#include "GraphicsComponent.h"
#include "Scene.h"
#include "utils.h"

class GridRenderComponent final : public GraphicsComponent
{
public:
	GridRenderComponent(const std::vector<utils::Tile*>& grid, Scene& scene);
	GridRenderComponent() = default;
	virtual ~GridRenderComponent() = default;
	GridRenderComponent(const GridRenderComponent & other) = delete;
	GridRenderComponent(GridRenderComponent && other) = delete;
	void operator=(const GridRenderComponent & rhs) = delete;
	void operator=(const GridRenderComponent && rhs) = delete;

	virtual void Update(float elapsedSec, GameObject & obj) override;

	void Render() const;
private:
	std::vector<utils::Tile*> m_Grid;
	std::shared_ptr<Texture2D> m_pTile2, m_pTile1, m_pTile3;
	const float m_TileOffsetX;
};
