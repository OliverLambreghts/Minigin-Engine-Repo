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
		: m_pActor(obj)
	{

	}

	virtual ~MoveDownLeftCommand() = default;
	MoveDownLeftCommand(const MoveDownLeftCommand& other) = delete;
	MoveDownLeftCommand(MoveDownLeftCommand&& other) = delete;
	MoveDownLeftCommand& operator=(const MoveDownLeftCommand& other) = delete;
	MoveDownLeftCommand& operator=(MoveDownLeftCommand&& other) = delete;
	
	virtual void Execute() override
	{
		if (!m_pActor->GetComponent<CoilyTransformComponent>())
			m_pActor->GetComponent<HexTransformComponent>()->Move(HexTransformComponent::Direction::downLeft);
		else if (m_pActor->GetComponent<CoilyTransformComponent>()->IsPlayerControlling())
			m_pActor->GetComponent<CoilyTransformComponent>()->Move(HexTransformComponent::Direction::downLeft);
	}
private:
	std::shared_ptr<GameObject> m_pActor;
};
