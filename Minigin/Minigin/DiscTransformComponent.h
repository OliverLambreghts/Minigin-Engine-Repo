#pragma once
#include "HexTransformComponent.h"

class DiscTransformComponent : public HexTransformComponent
{
public:
	DiscTransformComponent(std::shared_ptr<std::vector<utils::Tile*>>& grid, std::function<std::pair<int, int>()> getQbertPos,
		std::function<void(bool)> setTP);
	virtual ~DiscTransformComponent();
	DiscTransformComponent(const DiscTransformComponent& other) = delete;
	DiscTransformComponent(DiscTransformComponent&& other) = delete;
	void operator=(const DiscTransformComponent& rhs) = delete;
	void operator=(const DiscTransformComponent&& rhs) = delete;

	void InitPos();

	virtual void Update(float elapsedSec, GameObject& obj) override;
	void HandleTeleportActivity(GameObject& obj);
	
private:
	std::function<std::pair<int, int>()> m_QBertPos;
	std::function<void(bool)> m_SetTeleport;
	bool m_IsActive, m_HasBeenUsed;
	static int m_Counter;
	const float m_DiscOffsetX, m_DiscOffsetY;
};
