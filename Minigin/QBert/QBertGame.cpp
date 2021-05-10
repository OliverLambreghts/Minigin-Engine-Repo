#include "MiniginPCH.h"
#include "QBertGame.h"


#include "InputManager.h"
#include "SceneManager.h"
#include "Session.h"
#include "CatchSamSlickCommand.h"
#include "CoilyDefeatedDiscCommand.h"
#include "CoilyResetComponent.h"
#include "CoilyTransformComponent.h"
#include "ColorChangeCommand.h"
#include "DieCommand.h"
#include "DiscTransformComponent.h"
#include "FPSComponent.h"
#include "FullEnemyResetComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "TextComponent.h"
#include "TransformComponent.h"
#include "GraphicsComponent2D.h"
#include "GridComponent.h"
#include "GridRenderComponent.h"
#include "HealthComponent.h"
#include "HexTransformComponent.h"
#include "LivesDisplay.h"
#include "LoggingAudioService.h"
#include "MoveDownLeftCommand.h"
#include "MoveDownRightCommand.h"
#include "MoveTopLeftCommand.h"
#include "MoveTopRightCommand.h"
#include "PlayerComponent.h"
#include "RemainingDiscCommand.h"
#include "Resetter.h"
#include "ScoreComponent.h"
#include "ScoreDisplay.h"
#include "ServiceLocator.h"
#include "Session.h"
#include "SimpleSDL2AudioService.h"
#include "SlickSamResetComponent.h"
#include "SlickSamTransformComponent.h"
#include "TestSoundCommand.h"
#include "ThreadRAII.h"
#include "UggWrongwayResetComponent.h"
#include "UggWrongwayTransformComponent.h"
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
	auto grid = std::make_shared<std::vector<utils::Tile*>>();
	level->AddComponent(std::make_shared<GridComponent>(35.f, 7, m_WindowWidth, grid, 1));
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

	// --- RESETTER OBSERVER ---
	auto resetObserver = std::make_shared<Resetter>();
	// --- RESETTER OBSERVER ---

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
	auto healthComp = std::make_shared<HealthComponent>();
	QBert->AddComponent(healthComp);
	QBert->AddComponent(std::make_shared<PlayerComponent>());
	QBert->AddComponent(std::make_shared<ScoreComponent>());
	auto QBertTransformComp = std::make_shared<HexTransformComponent>(grid);
	QBert->AddComponent(QBertTransformComp);
	QBert->AddComponent(std::make_shared<GraphicsComponent2D>("../Data/QBert/Character/Right.png", scene));
	InputManager::GetInstance().AddCommand<MoveTopLeftCommand>(SDLK_LEFT,
		SDL_KEYUP, QBert);
	InputManager::GetInstance().AddCommand<MoveTopRightCommand>(SDLK_UP,
		SDL_KEYUP, QBert);
	InputManager::GetInstance().AddCommand<MoveDownLeftCommand>(SDLK_DOWN,
		SDL_KEYUP, QBert);
	InputManager::GetInstance().AddCommand<MoveDownRightCommand>(SDLK_RIGHT,
		SDL_KEYUP, QBert);

	InputManager::GetInstance().AddCommand<MoveTopLeftCommand>(ControllerKey(0, ControllerButton::ButtonLeft),
		XINPUT_KEYSTROKE_KEYUP, QBert);
	InputManager::GetInstance().AddCommand<MoveTopRightCommand>(ControllerKey(0, ControllerButton::ButtonUp),
		XINPUT_KEYSTROKE_KEYUP, QBert);
	InputManager::GetInstance().AddCommand<MoveDownLeftCommand>(ControllerKey(0, ControllerButton::ButtonDown),
		XINPUT_KEYSTROKE_KEYUP, QBert);
	InputManager::GetInstance().AddCommand<MoveDownRightCommand>(ControllerKey(0, ControllerButton::ButtonRight),
		XINPUT_KEYSTROKE_KEYUP, QBert);

	QBert->GetComponent<HealthComponent>()->GetSubject().AddObserver(livesDisplay);
	QBert->GetComponent<HealthComponent>()->GetSubject().AddObserver(resetObserver);
	QBert->GetComponent<ScoreComponent>()->GetSubject().AddObserver(scoreDisplay);
	scene.Add(QBert);

	// Fcn ptr that retuns QBert's position on the grid
	std::function<std::pair<int, int>()> getQBertPos = std::bind(&HexTransformComponent::GetRowCol, QBertTransformComp);
	// Give this function ptr to enemies so they can kill QBert when they come in contact
	std::function<void()> killFcn = std::bind(&HealthComponent::Kill, &*healthComp);
	// Fcn ptr that can set QBert's teleport flag
	std::function<void(bool)> setTP = std::bind(&HexTransformComponent::SetTeleport, QBertTransformComp, std::placeholders::_1);
	// ---------- NEW QBERT CODE ------------------------------

	// ----------- ENEMY CODE ---------------------------------
	// --- COILY ---
	auto coilyCmd = std::make_shared<CoilyDefeatedDiscCommand>(QBert);
	auto coily = std::make_shared<GameObject>();
	coily->AddComponent(std::make_shared<CoilyTransformComponent>(grid, getQBertPos, killFcn, coilyCmd));
	coily->AddComponent(std::make_shared<GraphicsComponent2D>("../Data/QBert/Enemies/Coily/Egg.png", scene));
	auto coilyResetComp = std::make_shared<CoilyResetComponent>();
	coily->AddComponent(coilyResetComp);
	coily->GetComponent<GraphicsComponent2D>()->SetVisibility(false);
	scene.Add(coily);

	// Coily's reset fcn ptr
	std::function<void()> coilyReset = std::bind(&CoilyResetComponent::Reset, coilyResetComp, coily);

	// --- UGG & WRONGWAY ---
	auto wrongway = std::make_shared<GameObject>();
	wrongway->AddComponent(std::make_shared<UggWrongWayTransformComponent>(grid, getQBertPos, killFcn,
		UggWrongWayTransformComponent::EntityType::wrongway));
	wrongway->AddComponent(std::make_shared<GraphicsComponent2D>("../Data/QBert/Enemies/Wrongway/Wrongway.png", scene));
	auto wrongwayResetComp = std::make_shared<UggWrongwayResetComponent>();
	wrongway->AddComponent(wrongwayResetComp);
	wrongway->GetComponent<GraphicsComponent2D>()->SetVisibility(false);
	scene.Add(wrongway);
	// Wrongway's reset fcn ptr
	std::function<void()> wrongwayReset = std::bind(&UggWrongwayResetComponent::Reset, wrongwayResetComp, wrongway);

	auto ugg = std::make_shared<GameObject>();
	ugg->AddComponent(std::make_shared<UggWrongWayTransformComponent>(grid, getQBertPos, killFcn,
		UggWrongWayTransformComponent::EntityType::ugg));
	ugg->AddComponent(std::make_shared<GraphicsComponent2D>("../Data/QBert/Enemies/Ugg/Ugg.png", scene));
	auto uggResetComp = std::make_shared<UggWrongwayResetComponent>();
	ugg->AddComponent(uggResetComp);
	ugg->GetComponent<GraphicsComponent2D>()->SetVisibility(false);
	scene.Add(ugg);
	// Ugg's reset fcn ptr
	std::function<void()> uggReset = std::bind(&UggWrongwayResetComponent::Reset, uggResetComp, ugg);

	// --- SLICK & SAM ---
	auto slickSamDefeatCmd = std::make_shared<CatchSamSlickCommand>(QBert);
	auto slick = std::make_shared<GameObject>();
	slick->AddComponent(std::make_shared<SlickSamTransformComponent>(grid, getQBertPos, SlickSamTransformComponent::EntityType::slick, slickSamDefeatCmd));
	slick->AddComponent(std::make_shared<GraphicsComponent2D>("../Data/QBert/Enemies/Slick/Slick.png", scene));
	auto slickResetComp = std::make_shared<SlickSamResetComponent>();
	slick->AddComponent(slickResetComp);
	slick->GetComponent<GraphicsComponent2D>()->SetVisibility(false);
	scene.Add(slick);

	// Slick's reset fcn ptr
	std::function<void()> slickReset = std::bind(&SlickSamResetComponent::Reset, slickResetComp, slick);

	auto sam = std::make_shared<GameObject>();
	sam->AddComponent(std::make_shared<SlickSamTransformComponent>(grid, getQBertPos, SlickSamTransformComponent::EntityType::sam, slickSamDefeatCmd));
	sam->AddComponent(std::make_shared<GraphicsComponent2D>("../Data/QBert/Enemies/Sam/Sam.png", scene));
	auto samResetComp = std::make_shared<SlickSamResetComponent>();
	sam->AddComponent(samResetComp);
	sam->GetComponent<GraphicsComponent2D>()->SetVisibility(false);
	scene.Add(sam);

	// Slick's reset fcn ptr
	std::function<void()> samReset = std::bind(&SlickSamResetComponent::Reset, samResetComp, sam);
	// ----------- ENEMY CODE ---------------------------------

	// ----------- ENEMY RESETTER ------------------
	auto enemyResetter = std::make_shared<GameObject>();
	auto fullResetComp = std::make_shared<FullEnemyResetComponent>();
	enemyResetter->AddComponent(fullResetComp);
	// -------- !!!ADD ALL ENEMIES' RESET FUNCTIONS HERE!!! --------
	enemyResetter->GetComponent<FullEnemyResetComponent>()->AddResetter(coilyReset);
	enemyResetter->GetComponent<FullEnemyResetComponent>()->AddResetter(wrongwayReset);
	enemyResetter->GetComponent<FullEnemyResetComponent>()->AddResetter(uggReset);
	enemyResetter->GetComponent<FullEnemyResetComponent>()->AddResetter(slickReset);
	enemyResetter->GetComponent<FullEnemyResetComponent>()->AddResetter(samReset);
	// -------- !!!ADD ALL ENEMIES' RESET FUNCTIONS HERE!!! --------
	std::function<void()> resetAllFcn = std::bind(&FullEnemyResetComponent::ResetAll, fullResetComp);
	// Add the ResetAll method to the resetter observer
	resetObserver->AddData(resetAllFcn);
	scene.Add(enemyResetter);
	// ----------- ENEMY RESETTER ------------------

	// --- DISCS ---
	auto leftDisc = std::make_shared<GameObject>();
	leftDisc->AddComponent(std::make_shared<DiscTransformComponent>(grid, getQBertPos, setTP));
	leftDisc->AddComponent(std::make_shared<GraphicsComponent2D>("../Data/QBert/Objects/Disc.png", scene));
	scene.Add(leftDisc);

	auto rightDisc = std::make_shared<GameObject>();
	rightDisc->AddComponent(std::make_shared<DiscTransformComponent>(grid, getQBertPos, setTP));
	rightDisc->AddComponent(std::make_shared<GraphicsComponent2D>("../Data/QBert/Objects/Disc.png", scene));
	scene.Add(rightDisc);
	// --- DISCS ---
	Session::GetInstance().EndSession();
}
