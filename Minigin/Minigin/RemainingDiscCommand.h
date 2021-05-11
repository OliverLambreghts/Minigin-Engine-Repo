#pragma once
#include "Command.h"
#include "ScoreComponent.h"

namespace dae
{
	class GameObject;
}

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
		m_Actor.lock()->GetComponent<ScoreComponent>()->SetScoreEvent(Message::RemainingDisc);
	}
private:
	std::weak_ptr<GameObject> m_Actor;
};
