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
#include "TestSoundCommand.h"
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
	//Session::GetInstance().BeginSession();

	//InputManager::GetInstance().AddController();
	//InputManager::GetInstance().AddController();

	//auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	//auto go = std::make_shared<GameObject>();
	//go->AddComponent(std::make_shared<GraphicsComponent2D>("background.jpg", scene));
	//go->AddComponent(std::make_shared<TransformComponent>(0.f, 0.f));
	//scene.Add(go);

	//go = std::make_shared<GameObject>();
	//go->AddComponent(std::make_shared<GraphicsComponent2D>("logo.png", scene));
	//go->AddComponent(std::make_shared<TransformComponent>(216.f, 180.f));
	//scene.Add(go);

	//auto to = std::make_shared<GameObject>();
	//to->AddComponent(std::make_shared<TextComponent>
	//	("Lingua.otf", 36, SDL_Color{ 255,255,255 }, scene, "Programming 4 Assignment"));
	//to->AddComponent(std::make_shared<TransformComponent>(80.f, 20.f));
	//scene.Add(to);

	//// Level Game Object
	//auto level = std::make_shared<GameObject>();
	//level->AddComponent(std::make_shared<GridComponent>(50.f, 1));
	//level->AddComponent(std::make_shared<GridRenderComponent>(level->GetComponent<GridComponent>()->GetVertices(), scene));
	//scene.Add(level);

	//// FPS Counter
	//const unsigned int fontSize = 16;
	//auto FPSCounter = std::make_shared<GameObject>();
	//FPSCounter->AddComponent(std::make_shared<TextComponent>("Lingua.otf", fontSize, SDL_Color{ 0, 255, 0 }, scene));
	//FPSCounter->AddComponent(std::make_shared<TransformComponent>(10.f, float(fontSize)));
	//FPSCounter->AddComponent(std::make_shared<FPSComponent>());

	//// Data transfer
	//FPSCounter->GetDataManager().LinkData<std::string, FPSComponent, TextComponent>(
	//	FPSCounter->GetComponent<FPSComponent>().get(), &FPSComponent::GetFPS,
	//	FPSCounter->GetComponent<TextComponent>().get(), &TextComponent::SetText);

	//scene.Add(FPSCounter);

	//// Modes
	//auto modesWindow = std::make_shared<GameObject>();
	//modesWindow->AddComponent(std::make_shared<UIWindowComponent>(scene, "Main Menu"));
	//modesWindow->GetComponent<UIWindowComponent>()->AddElement(std::make_shared<UIButton>("Singleplayer", true));
	//modesWindow->GetComponent<UIWindowComponent>()->AddElement(std::make_shared<UIButton>("Co-op", true));
	//modesWindow->GetComponent<UIWindowComponent>()->AddElement(std::make_shared<UIButton>("Versus", true));
	//auto controlsButton = std::make_shared<UIButton>("Controls", true);
	//modesWindow->GetComponent<UIWindowComponent>()->AddElement(controlsButton);

	//// Sound test button
	//modesWindow->GetComponent<UIWindowComponent>()->AddElement(std::make_shared<UIButton>("Test Sound", false));
	//modesWindow->GetComponent<UIWindowComponent>()->AddCommand<TestSoundCommand>(4);
	//
	//scene.Add(modesWindow);

	//// Controls
	//auto controlsWindow = std::make_shared<GameObject>();
	//controlsWindow->AddComponent(std::make_shared<UIWindowComponent>(scene, "Controls"));
	//controlsWindow->GetComponent<UIWindowComponent>()->AddActivationButton(controlsButton);
	//controlsWindow->GetComponent<UIWindowComponent>()->AddElement(std::make_shared<UIText>
	//	("Button B: Die\nLeft Arrow: Color Change\nUp Arrow: Defeated Coily with Disc\nDown Arrow: Remaining Disc\nRight Arrow: Caught Sam/Slick"));
	//scene.Add(controlsWindow);

	//// Observers:
	//auto livesDisplay = std::make_shared<LivesDisplay>((UINT)InputManager::GetInstance().GetControllers().size());
	//auto scoreDisplay = std::make_shared<ScoreDisplay>();

	//// Players + ScoreDisplayUI + LivesDisplayUI
	//for (UINT i{}; i < (UINT)InputManager::GetInstance().GetControllers().size(); ++i)
	//{
	//	auto livesDisplayUI = std::make_shared<GameObject>();
	//	livesDisplayUI->AddComponent(std::make_shared<TextComponent>("Lingua.otf", 16, SDL_Color{ 0, 255, 0 }, scene));
	//	livesDisplay->AddData(*livesDisplayUI);
	//	scene.Add(livesDisplayUI);

	//	auto scoreDisplayUI = std::make_shared<GameObject>();
	//	scoreDisplayUI->AddComponent(std::make_shared<TextComponent>("Lingua.otf", 16, SDL_Color{ 0, 255, 0 }, scene));
	//	scoreDisplay->AddData(*scoreDisplayUI);
	//	scene.Add(scoreDisplayUI);

	//	auto QBert = std::make_shared<GameObject>();
	//	QBert->SetEntity(EntityType::Player);
	//	QBert->AddComponent(std::make_shared<HealthComponent>());
	//	QBert->AddComponent(std::make_shared<PlayerComponent>());
	//	QBert->AddComponent(std::make_shared<ScoreComponent>());
	//	InputManager::GetInstance().AddCommand<DieCommand>(ControllerKey(i, ControllerButton::ButtonB),
	//		XINPUT_KEYSTROKE_KEYUP, QBert);
	//	// SCORE COMMANDS (used for testing)
	//	InputManager::GetInstance().AddCommand<ColorChangeCommand>(ControllerKey(i, ControllerButton::ButtonLeft),
	//		XINPUT_KEYSTROKE_KEYUP, QBert);
	//	InputManager::GetInstance().AddCommand<CoilyDefeatedDiscCommand>(ControllerKey(i, ControllerButton::ButtonUp),
	//		XINPUT_KEYSTROKE_KEYUP, QBert);
	//	InputManager::GetInstance().AddCommand<RemainingDiscCommand>(ControllerKey(i, ControllerButton::ButtonDown),
	//		XINPUT_KEYSTROKE_KEYUP, QBert);
	//	InputManager::GetInstance().AddCommand<CatchSamSlickCommand>(ControllerKey(i, ControllerButton::ButtonRight),
	//		XINPUT_KEYSTROKE_KEYUP, QBert);
	//	QBert->GetComponent<HealthComponent>()->GetSubject().AddObserver(livesDisplay);
	//	QBert->GetComponent<ScoreComponent>()->GetSubject().AddObserver(scoreDisplay);
	//	scene.Add(QBert);
	//}

	//Session::GetInstance().EndSession();
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

		//auto* audioService = ServiceLocator::GetAudioService();



		while (doContinue)
		{
			const auto currentTime = high_resolution_clock::now();
			const float elapsedSec = duration<float>(currentTime - previousTime).count();

			previousTime = currentTime;

			doContinue = input.ProcessInput();

			// Add audio system to a separate thread for processing sounds:

			//std::thread audioThread{ &AudioService::Update, audioService };
			//ThreadRAII audioThreadRAII{ audioThread };

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