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
		: m_pActor(obj)
	{

	}

	virtual ~MoveDownRightCommand() = default;
	MoveDownRightCommand(const MoveDownRightCommand& other) = delete;
	MoveDownRightCommand(MoveDownRightCommand&& other) = delete;
	MoveDownRightCommand& operator=(const MoveDownRightCommand& other) = delete;
	MoveDownRightCommand& operator=(MoveDownRightCommand&& other) = delete;
	
	virtual void Execute() override
	{
		if (!m_pActor->GetComponent<CoilyTransformComponent>())
			m_pActor->GetComponent<HexTransformComponent>()->Move(HexTransformComponent::Direction::downRight);
		else if (m_pActor->GetComponent<CoilyTransformComponent>()->IsPlayerControlling())
			m_pActor->GetComponent<CoilyTransformComponent>()->Move(HexTransformComponent::Direction::downRight);
	}
private:
	std::shared_ptr<GameObject> m_pActor;
};
