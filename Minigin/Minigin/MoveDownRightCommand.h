#pragma once
#include "Command.h"
#include "HexTransformComponent.h"
#include "CoilyTransformComponent.h"

namespace dae
{
	class GameObject;
}

class MoveDownRightCommand final : public Command
{
public:
	MoveDownRightCommand(std::shared_ptr<dae::GameObject>& obj)
		: m_Actor(obj)
	{

	}

	virtual ~MoveDownRightCommand() = default;
	virtual void Execute() override
	{
		if (!m_Actor->GetComponent<CoilyTransformComponent>())
			m_Actor->GetComponent<HexTransformComponent>()->Move(HexTransformComponent::Direction::downRight);
		else if (m_Actor->GetComponent<CoilyTransformComponent>()->IsPlayerControlling())
			m_Actor->GetComponent<CoilyTransformComponent>()->Move(HexTransformComponent::Direction::downRight);
	}
private:
	std::shared_ptr<GameObject> m_Actor;
};
