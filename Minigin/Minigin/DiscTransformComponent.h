#pragma once
#include "HexTransformComponent.h"
#include "RemainingDiscCommand.h"

class DiscTransformComponent : public HexTransformComponent
{
public:
	DiscTransformComponent(std::shared_ptr<std::vector<utils::Tile*>>& grid, std::function<std::pair<int, int>()> getQbertPos,
		std::function<void(bool)> setTP, std::function<const bool()> hasLevelEnded, std::shared_ptr<RemainingDiscCommand> discCMD, bool left,
		std::function<std::pair<int, int>()> getQbertPos2,
		std::function<void(bool)> setTP2);
	virtual ~DiscTransformComponent();
	DiscTransformComponent(const DiscTransformComponent& other) = delete;
	DiscTransformComponent(DiscTransformComponent&& other) = delete;
	void operator=(const DiscTransformComponent& rhs) = delete;
	void operator=(const DiscTransformComponent&& rhs) = delete;

	void InitPos(bool left);

	virtual void Update(float elapsedSec, GameObject& obj) override;
	void HandleTeleportActivity(GameObject& obj);
	
private:
	std::function<std::pair<int, int>()> m_QBertPos, m_QBertPos2;
	std::function<void(bool)> m_SetTeleport, m_SetTeleport2;
	std::function<const bool()> m_HasLevelEnded;
	bool m_IsActive, m_HasBeenUsed, m_HasScoreChanged;
	static int m_Counter;
	const float m_DiscOffsetX, m_DiscOffsetY;
	std::shared_ptr<RemainingDiscCommand> m_DiscCMD;
};
