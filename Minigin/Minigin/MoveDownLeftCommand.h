#pragma once
#include "Command.h"
#include "HexTransformComponent.h"

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
		m_Actor->GetComponent<HexTransformComponent>()->Move(HexTransformComponent::Direction::downLeft);
	}
private:
	std::shared_ptr<GameObject> m_Actor;
};
