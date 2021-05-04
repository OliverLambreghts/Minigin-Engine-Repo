#pragma once
#include "EnemyResetComponent.h"

class UggWrongwayResetComponent : public EnemyResetComponent
{
public:
	UggWrongwayResetComponent() = default;
	virtual ~UggWrongwayResetComponent() = default;
	UggWrongwayResetComponent(const UggWrongwayResetComponent& other) = delete;
	UggWrongwayResetComponent(UggWrongwayResetComponent&& other) = delete;
	void operator=(const UggWrongwayResetComponent& rhs) = delete;
	void operator=(const UggWrongwayResetComponent&& rhs) = delete;

	virtual void Update(float elapsedSec, GameObject & obj) override;

	virtual void Reset(std::shared_ptr<GameObject>&ptr) override;
private:
	
};
