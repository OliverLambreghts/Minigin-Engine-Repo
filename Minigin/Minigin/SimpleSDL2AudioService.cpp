#include "MiniginPCH.h"
#include "SimpleSDL2AudioService.h"
#include "audio.h"

std::deque<AudioRequest> SimpleSDL2AudioService::m_EventQueue{};
std::mutex SimpleSDL2AudioService::m_Mutex{};
std::condition_variable SimpleSDL2AudioService::m_CV{};

void SimpleSDL2AudioService::PlaySound(const char* filename, int volume)
{
	std::lock_guard<std::mutex> lock{ m_Mutex };
	for(auto& request : m_EventQueue)
	{
		if(filename == request.fileName)
		{
			if (volume > request.volume)
				request.volume = volume;
			return;
		}
	}
	
	AudioRequest request{ true, filename, volume };
	m_EventQueue.push_back(request);
	m_CV.notify_one();
}

void SimpleSDL2AudioService::PlayMusic(const char* filename, int volume)
{
	std::lock_guard<std::mutex> lock{ m_Mutex };
	for (auto& request : m_EventQueue)
	{
		if (filename == request.fileName)
		{
			if (volume > request.volume)
				request.volume = volume;
			return;
		}
	}

	AudioRequest request{ false, filename, volume };
	m_EventQueue.push_back(request);
	m_CV.notify_one();
}

void SimpleSDL2AudioService::InitAudio()
{
	initAudio();
}

void SimpleSDL2AudioService::EndAudio()
{
	endAudio();
}

void SimpleSDL2AudioService::PauseAudio()
{
	pauseAudio();
}

void SimpleSDL2AudioService::UnpauseAudio()
{
	unpauseAudio();
}

SimpleSDL2AudioService::~SimpleSDL2AudioService()
{
	endAudio();
}

void SimpleSDL2AudioService::Update()
{
	if (m_EventQueue.empty()) return;
	
	std::unique_lock<std::mutex> lock{ m_Mutex };
	m_CV.wait(lock, []() {return (m_EventQueue.empty()) ? false : true; });
	
	const auto& request = m_EventQueue.front();
	if (request.isSound)
		playSound(request.fileName, request.volume);
	else playMusic(request.fileName, request.volume);
	m_EventQueue.pop_front();
}