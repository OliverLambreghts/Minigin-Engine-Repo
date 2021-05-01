#pragma once
#include "GameplayComponent.h"

class FullEnemyResetComponent : public GameplayComponent
{
public:
	virtual void Update(float elapsedSec, GameObject& obj) override;

	void ResetAll();

	void AddResetter(std::function<void()>& resetter);
private:
	std::vector<std::function<void()>> m_pResetFcns;
};
