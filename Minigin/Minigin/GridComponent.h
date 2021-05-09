#pragma once
#include "CalculationComponent.h"
#include "utils.h"

class GridComponent : public CalculationComponent
{
public:
	GridComponent(float hexSize, int hexAmount, int windowWidth, std::shared_ptr<std::vector<utils::Tile1>>& grid);
	virtual ~GridComponent() = default;
	GridComponent(const GridComponent & other) = delete;
	GridComponent(GridComponent && other) = delete;
	void operator=(const GridComponent & rhs) = delete;
	void operator=(const GridComponent && rhs) = delete;

	virtual void Update(float elapsedSec, GameObject & obj) override;
	const std::vector<utils::Tile1>& GetVertices() const;
private:
	float m_HexSize;
	int m_HexAmount;
	std::shared_ptr<std::vector<utils::Tile1>> m_Tiles;
};
