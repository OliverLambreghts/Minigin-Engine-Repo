#pragma once
#include "EnemyState.h"

class EggState final : public EnemyState
{
public:
	EggState() = default;
	virtual ~EggState() = default;
	EggState(const EggState& other) = default;
	EggState(EggState&& other) = delete;
	void operator=(const EggState& rhs) = delete;
	void operator=(const EggState&& rhs) = delete;
	
	virtual std::shared_ptr<EnemyState> Update(float elapsedSec, dae::GameObject& obj) override;
private:
	float m_Timer = 0.f;
};
