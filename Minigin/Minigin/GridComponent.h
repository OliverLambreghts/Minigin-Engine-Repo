#pragma once
#include "CalculationComponent.h"
#include "utils.h"

class GridComponent final : public CalculationComponent
{
public:
	GridComponent(float hexSize, int hexAmount, int windowWidth, std::shared_ptr<std::vector<utils::Tile*>>& grid, int level);
	virtual ~GridComponent();
	GridComponent(const GridComponent & other) = delete;
	GridComponent(GridComponent && other) = delete;
	void operator=(const GridComponent & rhs) = delete;
	void operator=(const GridComponent && rhs) = delete;

	virtual void Update(float elapsedSec, GameObject & obj) override;
	const std::vector<utils::Tile*>& GetVertices() const;
	bool HasLevelEnded() const;
private:
	float m_HexSize;
	int m_HexAmount;
	std::shared_ptr<std::vector<utils::Tile*>> m_pTiles;
	bool m_IsLevelComplete;
	float m_EndTimer;
	int m_WindowWidth;
};
