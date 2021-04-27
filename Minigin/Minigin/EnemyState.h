#pragma once
#include "GameObject.h"

class EnemyState
{
public:
	virtual ~EnemyState() = default;
	virtual void Update(float elapsedSec, dae::GameObject& obj) = 0;
};
