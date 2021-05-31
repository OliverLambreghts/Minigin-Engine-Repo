#pragma once
#include "Command.h"
#include "HexTransformComponent.h"
#include "CoilyTransformComponent.h"

namespace dae
{
	class GameObject;
}

class MoveTopLeftCommand final : public Command
{
public:
	MoveTopLeftCommand(std::shared_ptr<dae::GameObject>& obj)
		: m_pActor(obj)
	{

	}

	virtual ~MoveTopLeftCommand() = default;
	MoveTopLeftCommand(const MoveTopLeftCommand& other) = delete;
	MoveTopLeftCommand(MoveTopLeftCommand&& other) = delete;
	MoveTopLeftCommand& operator=(const MoveTopLeftCommand& other) = delete;
	MoveTopLeftCommand& operator=(MoveTopLeftCommand&& other) = delete;
	
	virtual void Execute() override
	{
		if (!m_pActor->GetComponent<CoilyTransformComponent>())
			m_pActor->GetComponent<HexTransformComponent>()->Move(HexTransformComponent::Direction::topLeft);
		else if (m_pActor->GetComponent<CoilyTransformComponent>()->IsPlayerControlling())
			m_pActor->GetComponent<CoilyTransformComponent>()->Move(HexTransformComponent::Direction::topLeft);
	}
private:
	std::shared_ptr<GameObject> m_pActor;
};
