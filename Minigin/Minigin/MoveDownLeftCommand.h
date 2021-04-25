#pragma once
#include "Command.h"
#include "QBertTransformComponent.h"

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
		m_Actor->GetComponent<QBertTransformComponent>()->Move(QBertTransformComponent::Direction::downLeft);
	}
private:
	std::shared_ptr<GameObject> m_Actor;
};
