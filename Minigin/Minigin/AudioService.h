#pragma once

// Abstract audio interface
class AudioService
{
public:
	virtual ~AudioService() = default;
	
	virtual void PlaySound(const char* filename, int volume) = 0;
	virtual void PlayMusic(const char* filename, int volume) = 0;
	virtual void PauseAudio() = 0;
	virtual void UnpauseAudio() = 0;
	virtual void Update() = 0;
	virtual void SetVolume(int volume) = 0;
};