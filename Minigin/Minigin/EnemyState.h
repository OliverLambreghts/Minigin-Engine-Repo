#pragma once
#include "GameObject.h"

class EnemyState
{
public:
	virtual ~EnemyState() = default;
	virtual std::shared_ptr<EnemyState> Update(float elapsedSec, dae::GameObject& obj) = 0;
};
