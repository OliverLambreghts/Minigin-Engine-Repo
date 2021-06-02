#pragma once
#include "Command.h"
#include "ScoreComponent.h"

namespace dae
{
	class GameObject;
}

class CoilyDefeatedDiscCommand final : public Command
{
public:
	explicit CoilyDefeatedDiscCommand(std::shared_ptr<dae::GameObject>& obj)
		: m_pActor{ obj }
	{

	}

	virtual ~CoilyDefeatedDiscCommand() = default;
	CoilyDefeatedDiscCommand(const CoilyDefeatedDiscCommand& other) = delete;
	CoilyDefeatedDiscCommand(CoilyDefeatedDiscCommand&& other) = delete;
	CoilyDefeatedDiscCommand& operator=(const CoilyDefeatedDiscCommand& other) = delete;
	CoilyDefeatedDiscCommand& operator=(CoilyDefeatedDiscCommand&& other) = delete;
	
	virtual void Execute() override
	{
		m_pActor.lock()->GetComponent<ScoreComponent>()->SetScoreEvent(Message::CoilyDefeatedDisc);
	}
private:
	std::weak_ptr<GameObject> m_pActor;
};
