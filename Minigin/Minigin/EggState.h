#pragma once
#include "EnemyState.h"

class EggState : public EnemyState
{
public:
	virtual ~EggState() = default;
	virtual void Update(float elapsedSec, dae::GameObject& obj) override;
};
