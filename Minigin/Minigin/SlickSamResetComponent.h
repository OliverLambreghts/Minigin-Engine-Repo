#pragma once
#include "EnemyResetComponent.h"

class SlickSamResetComponent final : public EnemyResetComponent
{
public:
	SlickSamResetComponent() = default;
	virtual ~SlickSamResetComponent() = default;
	SlickSamResetComponent(const SlickSamResetComponent& other) = delete;
	SlickSamResetComponent(SlickSamResetComponent&& other) = delete;
	void operator=(const SlickSamResetComponent& rhs) = delete;
	void operator=(const SlickSamResetComponent&& rhs) = delete;

	virtual void Update(float elapsedSec, GameObject & obj) override;

	virtual void Reset(std::shared_ptr<GameObject>&ptr) override;
private:
	
};
