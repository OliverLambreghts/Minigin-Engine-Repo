#pragma once
#include "Command.h"
#include "QBertTransformComponent.h"

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
		m_Actor->GetComponent<QBertTransformComponent>()->Move(QBertTransformComponent::Direction::downRight);
	}
private:
	std::shared_ptr<GameObject> m_Actor;
};
