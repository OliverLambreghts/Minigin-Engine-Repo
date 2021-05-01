#pragma once
#include "EnemyState.h"

class InvisibleState : public EnemyState
{
public:
	InvisibleState();
	virtual ~InvisibleState() = default;
	virtual std::shared_ptr<EnemyState> Update(float elapsedSec, dae::GameObject & obj) override;
private:
	float m_SpawnThreshold;
	float m_Timer;
};
