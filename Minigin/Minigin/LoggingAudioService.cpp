#include "MiniginPCH.h"
#include "LoggingAudioService.h"

#include "audio.h"

LoggingAudioService::LoggingAudioService(AudioService* service)
	: m_pRealService{ service },
	m_IsMuted{ true }
{

}

void LoggingAudioService::PlaySound(const char* filename, int volume)
{
	if(!m_IsMuted)
		m_pRealService->PlaySound(filename, volume);
	std::cout << "Playing " << filename << " at volume " << volume << std::endl;
}

void LoggingAudioService::PlayMusic(const char* filename, int volume)
{
	if (!m_IsMuted)
		m_pRealService->PlayMusic(filename, volume);
	std::cout << "Playing " << filename << " at volume " << volume << std::endl;
}

void LoggingAudioService::PauseAudio()
{
	if (!m_IsMuted)
		m_pRealService->PauseAudio();
	std::cout << "Audio paused\n";
}

void LoggingAudioService::UnpauseAudio()
{
	if (!m_IsMuted)
		m_pRealService->UnpauseAudio();
	std::cout << "Audio unpaused\n";
}

LoggingAudioService::~LoggingAudioService()
{
	delete m_pRealService;
	m_pRealService = nullptr;
}

void LoggingAudioService::Update()
{
	m_pRealService->Update();
}

void LoggingAudioService::SetVolume(int volume)
{
	m_pRealService->SetVolume(volume);
}