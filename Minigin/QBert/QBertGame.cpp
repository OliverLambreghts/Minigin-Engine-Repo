#include "MiniginPCH.h"
#include "QBertGame.h"


#include "InputManager.h"
#include "SceneManager.h"
#include "Session.h"
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
#include "MoveDownLeftCommand.h"
#include "MoveDownRightCommand.h"
#include "MoveTopLeftCommand.h"
#include "MoveTopRightCommand.h"
#include "PlayerComponent.h"
#include "QBertTransformComponent.h"
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

QBertGame::QBertGame()
	: Minigin("QBert - Oliver Lambreghts")
{

}

void QBertGame::LoadGame() const
{
	Session::GetInstance().BeginSession();

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

	// Level Game Object
	auto level = std::make_shared<GameObject>();
	level->AddComponent(std::make_shared<GridComponent>(35.f, 7, m_WindowWidth));
	level->AddComponent(std::make_shared<GridRenderComponent>(level->GetComponent<GridComponent>()->GetVertices(), scene));
	scene.Add(level);

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
	modesWindow->AddComponent(std::make_shared<UIWindowComponent>(scene, "Main Menu"));
	modesWindow->GetComponent<UIWindowComponent>()->AddElement(std::make_shared<UIButton>("Singleplayer", true));
	modesWindow->GetComponent<UIWindowComponent>()->AddElement(std::make_shared<UIButton>("Co-op", true));
	modesWindow->GetComponent<UIWindowComponent>()->AddElement(std::make_shared<UIButton>("Versus", true));
	auto controlsButton = std::make_shared<UIButton>("Controls", true);
	modesWindow->GetComponent<UIWindowComponent>()->AddElement(controlsButton);

	// Sound test button
	modesWindow->GetComponent<UIWindowComponent>()->AddElement(std::make_shared<UIButton>("Test Sound", false));
	modesWindow->GetComponent<UIWindowComponent>()->AddCommand<TestSoundCommand>(4);

	scene.Add(modesWindow);

	// Controls
	auto controlsWindow = std::make_shared<GameObject>();
	controlsWindow->AddComponent(std::make_shared<UIWindowComponent>(scene, "Controls"));
	controlsWindow->GetComponent<UIWindowComponent>()->AddActivationButton(controlsButton);
	controlsWindow->GetComponent<UIWindowComponent>()->AddElement(std::make_shared<UIText>
		("Button B: Die\nLeft Arrow: Color Change\nUp Arrow: Defeated Coily with Disc\nDown Arrow: Remaining Disc\nRight Arrow: Caught Sam/Slick"));
	scene.Add(controlsWindow);

	// Observers:
	auto livesDisplay = std::make_shared<LivesDisplay>((UINT)InputManager::GetInstance().GetControllers().size());
	auto scoreDisplay = std::make_shared<ScoreDisplay>();

	// Players + ScoreDisplayUI + LivesDisplayUI
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

	// ---------- NEW QBERT CODE ------------------------------

	auto livesDisplayUI = std::make_shared<GameObject>();
	livesDisplayUI->AddComponent(std::make_shared<TextComponent>("Lingua.otf", 16, SDL_Color{ 0, 255, 0 }, scene));
	livesDisplay->AddData(*livesDisplayUI);
	scene.Add(livesDisplayUI);

	auto scoreDisplayUI = std::make_shared<GameObject>();
	scoreDisplayUI->AddComponent(std::make_shared<TextComponent>("Lingua.otf", 16, SDL_Color{ 0, 255, 0 }, scene));
	scoreDisplay->AddData(*scoreDisplayUI);
	scene.Add(scoreDisplayUI);

	auto QBert = std::make_shared<GameObject>();
	QBert->SetEntity(EntityType::Player);
	QBert->AddComponent(std::make_shared<HealthComponent>());
	QBert->AddComponent(std::make_shared<PlayerComponent>());
	QBert->AddComponent(std::make_shared<ScoreComponent>());
	/*auto qBertPos = level->GetComponent<GridComponent>()->GetVertices()[0].center;
	qBertPos.y -= 45.f;
	qBertPos.x -= 12.5f;*/
	QBert->AddComponent(std::make_shared<QBertTransformComponent>(level->GetComponent<GridComponent>()->GetVertices()));
	QBert->AddComponent(std::make_shared<GraphicsComponent2D>("../Data/QBert/Character/Right.png", scene));
	InputManager::GetInstance().AddCommand<MoveTopLeftCommand>(SDLK_LEFT,
		SDL_KEYUP, QBert);
	InputManager::GetInstance().AddCommand<MoveTopRightCommand>(SDLK_UP,
		SDL_KEYUP, QBert);
	InputManager::GetInstance().AddCommand<MoveDownLeftCommand>(SDLK_DOWN,
		SDL_KEYUP, QBert);
	InputManager::GetInstance().AddCommand<MoveDownRightCommand>(SDLK_RIGHT,
		SDL_KEYUP, QBert);
	
	QBert->GetComponent<HealthComponent>()->GetSubject().AddObserver(livesDisplay);
	QBert->GetComponent<ScoreComponent>()->GetSubject().AddObserver(scoreDisplay);
	scene.Add(QBert);
	// ---------- NEW QBERT CODE ------------------------------

	Session::GetInstance().EndSession();
}
