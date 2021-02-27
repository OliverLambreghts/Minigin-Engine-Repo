#pragma once
#include "Command.h"
#include "GameObject.h"
#include "ScoreComponent.h"

class ColorChangeCommand final : public Command
{
public:
	ColorChangeCommand(std::shared_ptr<GameObject>& obj)
		: m_Actor(obj)
	{

	}

	virtual ~ColorChangeCommand() = default;
	virtual void Execute() override
	{
		m_Actor->GetComponent<ScoreComponent>()->SetScoreEvent(Message::ColorChange);
	}
private:
	std::shared_ptr<GameObject> m_Actor;
};
