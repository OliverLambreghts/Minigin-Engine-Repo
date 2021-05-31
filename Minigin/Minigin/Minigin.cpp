#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <GL/gl.h>
#include <GL/GLU.h>

#include "CatchSamSlickCommand.h"
#include "CoilyDefeatedDiscCommand.h"
#include "ColorChangeCommand.h"
#include "DieCommand.h"
#include "FPSComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "TextComponent.h"
#include "TransformComponent.h"
#include "GraphicsComponent2D.h"
#include "GridComponent.h"
#include "GridRenderComponent.h"
#include "HealthComponent.h"
#include "LivesDisplay.h"
#include "LoggingAudioService.h"
#include "PlayerComponent.h"
#include "RemainingDiscCommand.h"
#include "ScoreComponent.h"
#include "ScoreDisplay.h"
#include "ServiceLocator.h"
#include "Session.h"
#include "SimpleSDL2AudioService.h"
#include "ThreadRAII.h"
#include "UIButton.h"
#include "UIText.h"
#include "UIWindowComponent.h"

using namespace std::chrono;

dae::Minigin::Minigin()
	:m_ProgramName{ "Programming 4 Assignment" },
	m_Window{},
	m_WindowWidth{},
	m_WindowHeight{}
{

}

dae::Minigin::Minigin(const std::string& programName)
	: m_ProgramName{ programName },
	m_Window{},
	m_WindowWidth{},
	m_WindowHeight{}
{

}

void dae::Minigin::Initialize()
{
	m_WindowWidth = 640;
	m_WindowHeight = 480;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	m_Window = SDL_CreateWindow(
		m_ProgramName.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		m_WindowWidth,
		m_WindowHeight,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	// Create OpenGL context 
	auto context = SDL_GL_CreateContext(m_Window);
	if (context == nullptr)
	{
		std::cerr << "Error when calling SDL_GL_CreateContext: " << SDL_GetError() << std::endl;
		return;
	}

	// Set the Projection matrix to the identity matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set up a two-dimensional orthographic viewing region.
	gluOrtho2D(0, m_WindowWidth, 0, m_WindowHeight); // y from bottom to top

	// Set the viewport to the client window area
	// The viewport is the rectangular region of the window where the image is drawn.
	glViewport(0, 0, m_WindowWidth, m_WindowHeight);

	// Set the Modelview matrix to the identity matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Enable color blending and use alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Renderer::GetInstance().Init(m_Window);

	auto audio = new SimpleSDL2AudioService{};
	_putenv("SDL_AUDIODRIVER=DirectSound");
	SDL_Init(SDL_INIT_AUDIO);
	audio->InitAudio();
	ServiceLocator::Provide(/*new LoggingAudioService{ */audio /*}*/);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	ServiceLocator::Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& input = InputManager::GetInstance();

		// Game Loop
		auto previousTime = high_resolution_clock::now();
		bool doContinue = true;
		
		while (doContinue)
		{
			const auto currentTime = high_resolution_clock::now();
			const float elapsedSec = duration<float>(currentTime - previousTime).count();

			previousTime = currentTime;

			doContinue = input.ProcessInput();

			Update(elapsedSec);

			renderer.Render();

			auto sleepTime = duration_cast<duration<float>>(currentTime + milliseconds(MsPerFrame) - high_resolution_clock::now());
			std::this_thread::sleep_for(sleepTime);
		}
	}

	Cleanup();
}

void dae::Minigin::Update(float elapsedSec)
{
	auto& sceneManager = SceneManager::GetInstance();
	sceneManager.Update(elapsedSec);
}