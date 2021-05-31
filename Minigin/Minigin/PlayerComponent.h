#pragma once
#include "GameplayComponent.h"

class PlayerComponent final : public GameplayComponent
{
public:
	PlayerComponent(UINT playerID);
	virtual ~PlayerComponent() = default;
	PlayerComponent(const PlayerComponent& other) = delete;
	PlayerComponent(PlayerComponent&& other) = delete;
	void operator=(const PlayerComponent& rhs) = delete;
	void operator=(const PlayerComponent&& rhs) = delete;

	virtual void Update(float elapsedSec, GameObject& obj) override;

	UINT GetID() const;
private:
	UINT m_ID;
};