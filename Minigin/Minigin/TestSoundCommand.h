#pragma once
#include <SDL.h>
#include "Command.h"
#include "ServiceLocator.h"

class TestSoundCommand : public Command
{
public:
	virtual ~TestSoundCommand() = default;
	virtual void Execute()
	{
		ServiceLocator::GetAudioService()->PlaySound("../Data/Sounds/wow.wav", SDL_MIX_MAXVOLUME);
	}
};
