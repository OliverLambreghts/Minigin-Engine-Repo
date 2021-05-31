#pragma once
#include "Command.h"
#include "GameObject.h"
#include "ScoreComponent.h"

class ColorChangeCommand final : public Command
{
public:
	ColorChangeCommand(std::shared_ptr<GameObject>& obj)
		: m_pActor(obj)
	{

	}

	virtual ~ColorChangeCommand() = default;
	ColorChangeCommand(const ColorChangeCommand& other) = delete;
	ColorChangeCommand(ColorChangeCommand&& other) = delete;
	ColorChangeCommand& operator=(const ColorChangeCommand& other) = delete;
	ColorChangeCommand& operator=(ColorChangeCommand&& other) = delete;
	
	virtual void Execute() override
	{
		m_pActor->GetComponent<ScoreComponent>()->SetScoreEvent(Message::ColorChange);
	}
private:
	std::shared_ptr<GameObject> m_pActor;
};
