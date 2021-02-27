#pragma once
#include "Command.h"
#include "GameObject.h"
#include "ScoreComponent.h"

class CoilyDefeatedDiscCommand final : public Command
{
public:
	CoilyDefeatedDiscCommand(std::shared_ptr<GameObject>& obj)
		: m_Actor(obj)
	{

	}

	virtual ~CoilyDefeatedDiscCommand() = default;
	virtual void Execute() override
	{
		m_Actor->GetComponent<ScoreComponent>()->SetScoreEvent(Message::CoilyDefeatedDisc);
	}
private:
	std::shared_ptr<GameObject> m_Actor;
};
