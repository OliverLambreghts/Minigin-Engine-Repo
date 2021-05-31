#pragma once
#include "EnemyState.h"

class InvisibleState final : public EnemyState
{
public:
	InvisibleState();
	virtual ~InvisibleState() = default;
	InvisibleState(const InvisibleState& other) = default;
	InvisibleState(InvisibleState&& other) = delete;
	void operator=(const InvisibleState& rhs) = delete;
	void operator=(const InvisibleState&& rhs) = delete;
	
	virtual std::shared_ptr<EnemyState> Update(float elapsedSec, dae::GameObject & obj) override;
private:
	float m_SpawnThreshold;
	float m_Timer;
};
