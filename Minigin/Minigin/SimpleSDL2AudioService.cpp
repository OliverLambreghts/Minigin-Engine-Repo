#include "MiniginPCH.h"
#include "SimpleSDL2AudioService.h"
#include "audio.h"

std::deque<AudioRequest> SimpleSDL2AudioService::m_EventQueue{};
std::mutex SimpleSDL2AudioService::m_Mutex{};
std::condition_variable SimpleSDL2AudioService::m_CV{};
bool SimpleSDL2AudioService::m_IsDone{ false };

SimpleSDL2AudioService::SimpleSDL2AudioService()
	: m_AudioThread{ &SimpleSDL2AudioService::Update, this },
	m_Volume{ 20 }
{

}

void SimpleSDL2AudioService::PlaySound(const char* filename, int volume)
{
	std::lock_guard<std::mutex> lock{ m_Mutex };
	for (auto& request : m_EventQueue)
	{
		if (filename == request.fileName)
		{
			if(m_Volume != SDL_MIX_MAXVOLUME)
				request.volume = m_Volume;
			else if (volume > request.volume)
				request.volume = volume;
			return;
		}
	}

	AudioRequest request{ true, filename, m_Volume };
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
			if (m_Volume != SDL_MIX_MAXVOLUME)
				request.volume = m_Volume;
			else if (volume > request.volume)
				request.volume = volume;
			return;
		}
	}

	AudioRequest request{ false, filename, m_Volume };
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
	m_IsDone = true;
	m_CV.notify_one();
	m_AudioThread.join();
}

void SimpleSDL2AudioService::Update()
{
	do
	{
		std::unique_lock<std::mutex> lock{ m_Mutex };
		m_CV.wait(lock, []()
			{
				if (!m_EventQueue.empty() || m_IsDone)
				{
					return true;
				}
				return false;
			});
		if (m_IsDone)
			return;

		const auto& request = m_EventQueue.front();
		if (request.isSound)
			playSound(request.fileName, request.volume);
		else playMusic(request.fileName, request.volume);
		m_EventQueue.pop_front();
	} while (!m_IsDone);

	std::cout << "Thread exits\n";
}

void SimpleSDL2AudioService::SetVolume(int volume)
{
	m_Volume = volume;
}