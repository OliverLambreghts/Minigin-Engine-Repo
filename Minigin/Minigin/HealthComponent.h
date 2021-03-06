#pragma once
#include "GameplayComponent.h"
#include "Subject.h"

class HealthComponent : public GameplayComponent
{
public:
	HealthComponent() = default;
	virtual ~HealthComponent() = default;
	HealthComponent(const HealthComponent & other) = delete;
	HealthComponent(HealthComponent && other) = delete;
	void operator=(const HealthComponent & rhs) = delete;
	void operator=(const HealthComponent && rhs) = delete;

	virtual void Update(float elapsedSec, GameObject& obj) override;
	
	void SetHealth(int health);
	void Die(const GameObject& obj);

	Subject& GetSubject();
private:
	int m_Health = 100;
	Subject m_Subject;
};
