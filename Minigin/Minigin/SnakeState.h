#pragma once
#include "EnemyState.h"

class SnakeState final : public EnemyState
{
public:
	SnakeState() = default;
	virtual ~SnakeState() = default;
	SnakeState(const SnakeState& other) = default;
	SnakeState(SnakeState&& other) = delete;
	void operator=(const SnakeState& rhs) = delete;
	void operator=(const SnakeState&& rhs) = delete;
	
	virtual std::shared_ptr<EnemyState> Update(float elapsedSec, dae::GameObject & obj) override;
private:
	float m_Timer = 0.f;
};
