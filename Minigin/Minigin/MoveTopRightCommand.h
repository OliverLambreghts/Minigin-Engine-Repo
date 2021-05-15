#pragma once
#include "Command.h"
#include "HexTransformComponent.h"
#include "CoilyTransformComponent.h"

namespace dae
{
	class GameObject;
}

class MoveTopRightCommand final : public Command
{
public:
	MoveTopRightCommand(std::shared_ptr<dae::GameObject>& obj)
		: m_Actor(obj)
	{

	}

	virtual ~MoveTopRightCommand() = default;
	virtual void Execute() override
	{
		if (!m_Actor->GetComponent<CoilyTransformComponent>())
			m_Actor->GetComponent<HexTransformComponent>()->Move(HexTransformComponent::Direction::topRight);
		else if(m_Actor->GetComponent<CoilyTransformComponent>()->IsPlayerControlling())
			m_Actor->GetComponent<CoilyTransformComponent>()->Move(HexTransformComponent::Direction::topRight);
	}
private:
	std::shared_ptr<GameObject> m_Actor;
};
