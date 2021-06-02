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
	explicit CatchSamSlickCommand(std::shared_ptr<GameObject>& obj)
		: m_pActor(obj)
	{

	}

	virtual ~CatchSamSlickCommand() = default;
	CatchSamSlickCommand(const CatchSamSlickCommand& other) = delete;
	CatchSamSlickCommand(CatchSamSlickCommand&& other) = delete;
	CatchSamSlickCommand& operator=(const CatchSamSlickCommand& other) = delete;
	CatchSamSlickCommand& operator=(CatchSamSlickCommand&& other) = delete;
	
	virtual void Execute() override
	{
		m_pActor.lock()->GetComponent<ScoreComponent>()->SetScoreEvent(Message::CaughtSlickOrSam);
	}
private:
	std::weak_ptr<GameObject> m_pActor;
};
