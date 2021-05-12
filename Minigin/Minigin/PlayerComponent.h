#pragma once
#include "GameplayComponent.h"

class PlayerComponent : public GameplayComponent
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
	//static UINT m_CurrentID;
	UINT m_ID;
};