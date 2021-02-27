#pragma once
#include "Command.h"
#include "GameObject.h"
#include "ScoreComponent.h"

class RemainingDiscCommand final : public Command
{
public:
	RemainingDiscCommand(std::shared_ptr<GameObject>& obj)
		: m_Actor(obj)
	{

	}

	virtual ~RemainingDiscCommand() = default;
	virtual void Execute() override
	{
		m_Actor->GetComponent<ScoreComponent>()->SetScoreEvent(Message::RemainingDisc);
	}
private:
	std::shared_ptr<GameObject> m_Actor;
};
