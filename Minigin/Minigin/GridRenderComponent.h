#pragma once
#include "GraphicsComponent.h"
#include "Scene.h"
#include "utils.h"

class GridRenderComponent : public GraphicsComponent
{
public:
	GridRenderComponent(std::vector<utils::Tile> grid, Scene& scene);
	GridRenderComponent() = default;
	virtual ~GridRenderComponent() = default;
	GridRenderComponent(const GridRenderComponent & other) = delete;
	GridRenderComponent(GridRenderComponent && other) = delete;
	void operator=(const GridRenderComponent & rhs) = delete;
	void operator=(const GridRenderComponent && rhs) = delete;

	virtual void Update(float elapsedSec, GameObject & obj) override;

	void Render() const;
private:
	std::vector<utils::Tile> m_Grid;
};
