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
		: m_pActor(obj)
	{

	}

	virtual ~MoveTopRightCommand() = default;
	MoveTopRightCommand(const MoveTopRightCommand& other) = delete;
	MoveTopRightCommand(MoveTopRightCommand&& other) = delete;
	MoveTopRightCommand& operator=(const MoveTopRightCommand& other) = delete;
	MoveTopRightCommand& operator=(MoveTopRightCommand&& other) = delete;
	
	virtual void Execute() override
	{
		if (!m_pActor->GetComponent<CoilyTransformComponent>())
			m_pActor->GetComponent<HexTransformComponent>()->Move(HexTransformComponent::Direction::topRight);
		else if(m_pActor->GetComponent<CoilyTransformComponent>()->IsPlayerControlling())
			m_pActor->GetComponent<CoilyTransformComponent>()->Move(HexTransformComponent::Direction::topRight);
	}
private:
	std::shared_ptr<GameObject> m_pActor;
};
