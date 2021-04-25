#pragma once
#include "Command.h"
#include "QBertTransformComponent.h"

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
		m_Actor->GetComponent<QBertTransformComponent>()->Move(QBertTransformComponent::Direction::topRight);
	}
private:
	std::shared_ptr<GameObject> m_Actor;
};
