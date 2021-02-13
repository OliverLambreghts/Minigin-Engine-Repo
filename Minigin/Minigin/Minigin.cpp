#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>

#include "FPSComponent.h"
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"
#include "TextComponent.h"
#include "TransformComponent.h"

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
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<GameObject>();
	go->AddComponent("graphics", std::make_shared<GraphicsComponent>("background.jpg", scene, *go));
	go->AddComponent("transform", std::make_shared<TransformComponent>(0.f, 0.f, *go));
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->AddComponent("graphics", std::make_shared<GraphicsComponent>("logo.png", scene, *go));
	go->AddComponent("transform", std::make_shared<TransformComponent>(216.f, 180.f, *go));
	scene.Add(go);

	auto to = std::make_shared<GameObject>();
	to->AddComponent("graphics", std::make_shared<TextComponent>
		("Lingua.otf", 36, SDL_Color{ 255,255,255 }, "Programming 4 Assignment", scene, *to));
	to->AddComponent("transform", std::make_shared<TransformComponent>(80.f, 20.f, *go));
	scene.Add(to);

	const unsigned int fontSize = 16;
	auto FPSCounter = std::make_shared<GameObject>();
	const std::shared_ptr<TextComponent> textComponent = std::make_shared<TextComponent>
		( "Lingua.otf", fontSize, SDL_Color{ 0, 255, 0 }, "PH", scene, *FPSCounter );
	FPSCounter->AddComponent("graphics", textComponent);
	FPSCounter->AddComponent("transform", std::make_shared<TransformComponent>(10.f, float(fontSize), *FPSCounter));
	FPSCounter->AddComponent("calculation", std::make_shared<FPSComponent>(textComponent.get(), &TextComponent::SetText, *FPSCounter));
	scene.Add(FPSCounter);
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
		bool doContinue = true;
		auto previousTime = high_resolution_clock::now();
		auto lag = 0.f;
		const auto msPerUpdate = 2.f;
		while (doContinue)
		{
			const auto currentTime = high_resolution_clock::now();
			const float elapsedMs = float(duration_cast<milliseconds>(currentTime - previousTime).count());
			const float elapsedSec = elapsedMs / 1000;
			
			previousTime = currentTime;
			lag += elapsedMs;

			doContinue = input.ProcessInput();
			
			while(lag >= msPerUpdate)
			{
				Update(elapsedSec);
				lag -= msPerUpdate;
			}
			
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