#pragma once
#include "Command.h"
#include "HexTransformComponent.h"
#include "CoilyTransformComponent.h"

namespace dae
{
	class GameObject;
}

class MoveDownLeftCommand final : public Command
{
public:
	MoveDownLeftCommand(std::shared_ptr<dae::GameObject>& obj)
		: m_Actor(obj)
	{

	}

	virtual ~MoveDownLeftCommand() = default;
	virtual void Execute() override
	{
		if (!m_Actor->GetComponent<CoilyTransformComponent>())
			m_Actor->GetComponent<HexTransformComponent>()->Move(HexTransformComponent::Direction::downLeft);
		else if (m_Actor->GetComponent<CoilyTransformComponent>()->IsPlayerControlling())
			m_Actor->GetComponent<CoilyTransformComponent>()->Move(HexTransformComponent::Direction::downLeft);
	}
private:
	std::shared_ptr<GameObject> m_Actor;
};
