#pragma once
#include "EnemyState.h"

class EggState : public EnemyState
{
public:
	virtual ~EggState() = default;
	virtual std::shared_ptr<EnemyState> Update(float elapsedSec, dae::GameObject& obj) override;
private:
	float m_Timer = 0.f;
};
