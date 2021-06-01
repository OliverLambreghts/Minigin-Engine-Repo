#pragma once
#include "Command.h"
#include <memory>
#include <SDL.h>


#include "ServiceLocator.h"

namespace dae
{
	class GameObject;
}

class MuteCommand final : public Command
{
public:
	MuteCommand(std::shared_ptr<dae::GameObject>& obj)
		: m_pActor(obj)
	{

	}

	virtual ~MuteCommand() = default;
	MuteCommand(const MuteCommand& other) = delete;
	MuteCommand(MuteCommand&& other) = delete;
	MuteCommand& operator=(const MuteCommand& other) = delete;
	MuteCommand& operator=(MuteCommand&& other) = delete;

	virtual void Execute() override
	{
		m_IsMuted = !m_IsMuted;
		if (m_IsMuted)
			ServiceLocator::GetAudioService()->SetVolume(0);
		else
			ServiceLocator::GetAudioService()->SetVolume(m_DefaultVolume);
	}
private:
	std::weak_ptr<dae::GameObject> m_pActor;
	bool m_IsMuted = false;
	const int m_DefaultVolume = 20;
};