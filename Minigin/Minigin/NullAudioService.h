#pragma once
#include "AudioService.h"

class NullAudioService : public AudioService
{
public:
	virtual void PlaySound(const char*, int) override {};
	virtual void PlayMusic(const char*, int) override {};
	virtual void PauseAudio() override {};
	virtual void UnpauseAudio() override {};
	virtual void Update() override {};
	virtual void SetVolume(int ) override {};
};
