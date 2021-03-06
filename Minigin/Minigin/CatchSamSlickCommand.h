#pragma once
#include "Command.h"
#include "ScoreComponent.h"

namespace dae
{
	class GameObject;
}

class CatchSamSlickCommand final : public Command
{
public:
	CatchSamSlickCommand(std::shared_ptr<GameObject>& obj)
		: m_Actor(obj)
	{

	}

	virtual ~CatchSamSlickCommand() = default;
	virtual void Execute() override
	{
		m_Actor->GetComponent<ScoreComponent>()->SetScoreEvent(Message::CaughtSlickOrSam);
	}
private:
	std::shared_ptr<GameObject> m_Actor;
};
