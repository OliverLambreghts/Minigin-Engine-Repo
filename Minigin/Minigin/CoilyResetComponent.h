#pragma once
#include "EnemyResetComponent.h"
#include "Subject.h"

class CoilyResetComponent : public EnemyResetComponent
{
public:
	CoilyResetComponent() = default;
	virtual ~CoilyResetComponent() = default;
	CoilyResetComponent(const CoilyResetComponent& other) = delete;
	CoilyResetComponent(CoilyResetComponent&& other) = delete;
	void operator=(const CoilyResetComponent& rhs) = delete;
	void operator=(const CoilyResetComponent&& rhs) = delete;

	virtual void Update(float elapsedSec, GameObject & obj) override;

	virtual void Reset(std::shared_ptr<GameObject>& ptr) override;
private:
};
