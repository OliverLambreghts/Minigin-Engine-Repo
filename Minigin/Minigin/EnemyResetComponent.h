#pragma once
#include "GameplayComponent.h"

class EnemyResetComponent : public GameplayComponent
{
public:
	virtual ~EnemyResetComponent() = default;
	virtual void Reset(std::shared_ptr<GameObject>& ptr) = 0;
};
