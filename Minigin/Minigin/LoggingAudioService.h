#pragma once
#include "AudioService.h"

// Abstract audio interface
class LoggingAudioService : public AudioService
{
public:
	LoggingAudioService(AudioService* service);
	
	virtual ~LoggingAudioService();

	virtual void PlaySound(const char* filename, int volume) override;
	virtual void PlayMusic(const char* filename, int volume) override;
	virtual void PauseAudio() override;
	virtual void UnpauseAudio() override;
	virtual void Update() override;
private:
	AudioService* m_pRealService;
	bool m_IsMuted;
};