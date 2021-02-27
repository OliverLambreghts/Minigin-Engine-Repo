#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>



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
#include "HealthComponent.h"
#include "LivesDisplay.h"
#include "PlayerComponent.h"
#include "RemainingDiscCommand.h"
#include "ScoreComponent.h"
#include "ScoreDisplay.h"
#include "UIButton.h"
#include "UIText.h"
#include "UIWindowComponent.h"

using namespace std;
using namespace std::chrono;

void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	InputManager::GetInstance().AddController();
	InputManager::GetInstance().AddController();
	
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<GameObject>();
	go->AddComponent(std::make_shared<GraphicsComponent2D>("background.jpg", scene));
	go->AddComponent(std::make_shared<TransformComponent>(0.f, 0.f));
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->AddComponent(std::make_shared<GraphicsComponent2D>("logo.png", scene));
	go->AddComponent(std::make_shared<TransformComponent>(216.f, 180.f));
	scene.Add(go);

	auto to = std::make_shared<GameObject>();
	to->AddComponent(std::make_shared<TextComponent>
		("Lingua.otf", 36, SDL_Color{ 255,255,255 }, scene, "Programming 4 Assignment"));
	to->AddComponent(std::make_shared<TransformComponent>(80.f, 20.f));
	scene.Add(to);

	// FPS Counter
	const unsigned int fontSize = 16;
	auto FPSCounter = std::make_shared<GameObject>();
	FPSCounter->AddComponent(std::make_shared<TextComponent>("Lingua.otf", fontSize, SDL_Color{ 0, 255, 0 }, scene));
	FPSCounter->AddComponent(std::make_shared<TransformComponent>(10.f, float(fontSize)));
	FPSCounter->AddComponent(std::make_shared<FPSComponent>());

	// Data transfer
	FPSCounter->GetDataManager().LinkData<std::string, FPSComponent, TextComponent>(
		FPSCounter->GetComponent<FPSComponent>().get(), &FPSComponent::GetFPS,
		FPSCounter->GetComponent<TextComponent>().get(), &TextComponent::SetText);

	scene.Add(FPSCounter);

	// Modes
	auto modesWindow = std::make_shared<GameObject>();
	modesWindow->AddComponent(std::make_shared<UIWindowComponent>(scene, "Modes"));
	modesWindow->GetComponent<UIWindowComponent>()->AddElement(std::make_shared<UIButton>("Singleplayer"));
	modesWindow->GetComponent<UIWindowComponent>()->AddElement(std::make_shared<UIButton>("Co-op"));
	modesWindow->GetComponent<UIWindowComponent>()->AddElement(std::make_shared<UIButton>("Versus"));
	scene.Add(modesWindow);

	// Controls
	auto controlsWindow = std::make_shared<GameObject>();
	controlsWindow->AddComponent(std::make_shared<UIWindowComponent>(scene, "Controls"));
	controlsWindow->GetComponent<UIWindowComponent>()->AddElement(std::make_shared<UIText>
		("Button B: Die\nLeft Arrow: Color Change\nUp Arrow: Defeated Coily with Disc\nDown Arrow: Remaining Disc\nRight Arrow: Caught Sam/Slick"));
	scene.Add(controlsWindow);
	
	// Observers:
	auto livesDisplay = std::make_shared<LivesDisplay>(scene, (UINT)InputManager::GetInstance().GetControllers().size());
	auto scoreDisplay = std::make_shared<ScoreDisplay>(scene, (UINT)InputManager::GetInstance().GetControllers().size());
	
	// Players
	for (UINT i{}; i < (UINT)InputManager::GetInstance().GetControllers().size(); ++i)
	{
		auto QBert = std::make_shared<GameObject>();
		QBert->SetEntity(EntityType::Player);
		QBert->AddComponent(std::make_shared<HealthComponent>());
		QBert->AddComponent(std::make_shared<PlayerComponent>());
		QBert->AddComponent(std::make_shared<ScoreComponent>());
		InputManager::GetInstance().AddCommand<DieCommand>(ControllerKey(i, ControllerButton::ButtonB),
			XINPUT_KEYSTROKE_KEYUP, QBert);
		// SCORE COMMANDS (used for testing)
		InputManager::GetInstance().AddCommand<ColorChangeCommand>(ControllerKey(i, ControllerButton::ButtonLeft),
			XINPUT_KEYSTROKE_KEYUP, QBert);
		InputManager::GetInstance().AddCommand<CoilyDefeatedDiscCommand>(ControllerKey(i, ControllerButton::ButtonUp),
			XINPUT_KEYSTROKE_KEYUP, QBert);
		InputManager::GetInstance().AddCommand<RemainingDiscCommand>(ControllerKey(i, ControllerButton::ButtonDown),
			XINPUT_KEYSTROKE_KEYUP, QBert);
		InputManager::GetInstance().AddCommand<CatchSamSlickCommand>(ControllerKey(i, ControllerButton::ButtonRight),
			XINPUT_KEYSTROKE_KEYUP, QBert);
		QBert->GetComponent<HealthComponent>()->AddObserver(livesDisplay);
		QBert->GetComponent<ScoreComponent>()->AddObserver(scoreDisplay);
		scene.Add(QBert);
	}
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
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
			this_thread::sleep_for(sleepTime);
		}
	}

	Cleanup();
}

void dae::Minigin::Update(float elapsedSec)
{
	auto& sceneManager = SceneManager::GetInstance();
	sceneManager.Update(elapsedSec);
}