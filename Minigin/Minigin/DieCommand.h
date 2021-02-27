#pragma once
#include "Command.h"
#include "GameObject.h"
#include "HealthComponent.h"

class DieCommand final : public Command
{
public:
	DieCommand(std::shared_ptr<GameObject>& obj)
		: m_Actor(obj)
	{
		
	}
	
	virtual ~DieCommand() = default;
	virtual void Execute() override
	{
		m_Actor->GetComponent<HealthComponent>()->Die(*m_Actor);
	}
private:
	std::shared_ptr<GameObject> m_Actor;
};
