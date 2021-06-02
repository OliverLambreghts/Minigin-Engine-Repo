#pragma once
#include "Command.h"
#include "HealthComponent.h"

namespace dae
{
	class GameObject;
}

class DieCommand final : public Command
{
public:
	explicit DieCommand(std::shared_ptr<GameObject>& obj)
		: m_pActor(obj)
	{
		
	}
	
	virtual ~DieCommand() = default;
	DieCommand(const DieCommand& other) = delete;
	DieCommand(DieCommand&& other) = delete;
	DieCommand& operator=(const DieCommand& other) = delete;
	DieCommand& operator=(DieCommand&& other) = delete;
	
	virtual void Execute() override
	{
		m_pActor->GetComponent<HealthComponent>()->Die(*m_pActor);
	}
private:
	std::shared_ptr<GameObject> m_pActor;
};
