#pragma once
#include "Command.h"
#include "QBertTransformComponent.h"

namespace dae
{
	class GameObject;
}

class MoveTopLeftCommand final : public Command
{
public:
	MoveTopLeftCommand(std::shared_ptr<dae::GameObject>& obj)
		: m_Actor(obj)
	{

	}

	virtual ~MoveTopLeftCommand() = default;
	virtual void Execute() override
	{
		m_Actor->GetComponent<QBertTransformComponent>()->Move(QBertTransformComponent::Direction::topLeft);
	}
private:
	std::shared_ptr<GameObject> m_Actor;
};
