#pragma once
#include "CalculationComponent.h"
#include "utils.h"

class GridComponent : public CalculationComponent
{
public:
	GridComponent(float hexSize, int hexAmount, int windowWidth);
	virtual ~GridComponent() = default;
	GridComponent(const GridComponent & other) = delete;
	GridComponent(GridComponent && other) = delete;
	void operator=(const GridComponent & rhs) = delete;
	void operator=(const GridComponent && rhs) = delete;

	virtual void Update(float elapsedSec, GameObject & obj) override;
	const std::vector<utils::Tile>& GetVertices() const;
private:
	float m_HexSize;
	int m_HexAmount;
	std::vector<utils::Tile> m_Tiles;
};
