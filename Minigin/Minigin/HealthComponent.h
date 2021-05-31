#pragma once
#include "GameplayComponent.h"
#include "Subject.h"

class HealthComponent final : public GameplayComponent
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

	void Kill();
private:
	int m_Health = 100, m_Lives = 3;
	Subject m_Subject;
	bool m_CanDie = false;
};
