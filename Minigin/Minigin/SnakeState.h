#pragma once
#include "EnemyState.h"

class SnakeState : public EnemyState
{
public:
	virtual ~SnakeState() = default;
	virtual std::shared_ptr<EnemyState> Update(float elapsedSec, dae::GameObject & obj) override;
private:
	float m_Timer = 0.f;
};
