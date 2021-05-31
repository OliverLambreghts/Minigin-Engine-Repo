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
		: m_pActor(obj)
	{

	}

	virtual ~RemainingDiscCommand() = default;
	RemainingDiscCommand(const RemainingDiscCommand& other) = delete;
	RemainingDiscCommand(RemainingDiscCommand&& other) = delete;
	RemainingDiscCommand& operator=(const RemainingDiscCommand& other) = delete;
	RemainingDiscCommand& operator=(RemainingDiscCommand&& other) = delete;
	
	virtual void Execute() override
	{
		m_pActor.lock()->GetComponent<ScoreComponent>()->SetScoreEvent(Message::RemainingDisc);
	}
private:
	std::weak_ptr<GameObject> m_pActor;
};
