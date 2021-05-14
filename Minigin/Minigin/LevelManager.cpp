#include "MiniginPCH.h"
#include "LevelManager.h"


#include "GridComponent.h"
#include "utils.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include <string>

#include "SceneManager.h"

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
#include "GridRenderComponent.h"
#include "HealthComponent.h"
#include "HexTransformComponent.h"
#include "InputResetComponent.h"
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
#include "UIGameModeButton.h"

LevelManager::LevelManager(int windowWidth)
	: m_WindowWidth{ windowWidth },
	m_GameMode{std::make_shared<GameMode>()}
{

}

void LevelManager::LoadMainMenu()
{
	auto& scene = SceneManager::GetInstance().CreateScene("MainMenu");

	std::function<void(const std::wstring&)> loadLevel = std::bind(&LevelManager::LoadLevel, *this, std::placeholders::_1);
	
	// Modes
	auto modesWindow = std::make_shared<GameObject>();
	modesWindow->AddComponent(std::make_shared<UIWindowComponent>(scene, "Main Menu"));
	modesWindow->GetComponent<UIWindowComponent>()->AddElement(std::make_shared<UIGameModeButton>("Singleplayer", true, m_GameMode, GameMode::singleplayer, loadLevel));
	modesWindow->GetComponent<UIWindowComponent>()->AddElement(std::make_shared<UIGameModeButton>("Co-op", true, m_GameMode, GameMode::coop, loadLevel));
	modesWindow->GetComponent<UIWindowComponent>()->AddElement(std::make_shared<UIGameModeButton>("Versus", true, m_GameMode, GameMode::versus, loadLevel));
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

	scene.Activate();
}

void LevelManager::LoadLevel(const std::wstring& filePath)
{
	rapidjson::Document jsonDoc;
	ReadJSON(filePath, jsonDoc);

	// Parse level information
	std::string levelName = jsonDoc["levelName"].GetString();
	std::string tileType = jsonDoc["tileType"].GetString();
	auto tempArray = jsonDoc["enemies"].GetArray();
	std::vector<std::string> enemies;
	for (auto& enemy : tempArray)
		enemies.push_back(enemy.GetString());

	// Save level data
	LevelData levelData{ levelName, tileType, enemies };

	SetUpLevel(levelData);
}

void LevelManager::SetUpLevel(const LevelData& data)
{
	auto& scene = SceneManager::GetInstance().CreateScene(data.levelName);

	auto go = std::make_shared<GameObject>();
	go->AddComponent(std::make_shared<GraphicsComponent2D>("background.jpg", scene));
	go->AddComponent(std::make_shared<TransformComponent>(0.f, 0.f));
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->AddComponent(std::make_shared<GraphicsComponent2D>("logo.png", scene));
	go->AddComponent(std::make_shared<TransformComponent>(216.f, 180.f));
	scene.Add(go);

	auto to = std::make_shared<GameObject>();
	switch (*m_GameMode)
	{
	case GameMode::singleplayer:
		to->AddComponent(std::make_shared<TextComponent>
			("Lingua.otf", 36, SDL_Color{ 255,255,255 }, scene, "Singleplayer"));
		to->AddComponent(std::make_shared<TransformComponent>(220.f, 5.f));
		break;
	case GameMode::coop:
		to->AddComponent(std::make_shared<TextComponent>
			("Lingua.otf", 36, SDL_Color{ 255,255,255 }, scene, "Co-op"));
		to->AddComponent(std::make_shared<TransformComponent>(270.f, 5.f));
		break;
	case GameMode::versus:
		to->AddComponent(std::make_shared<TextComponent>
			("Lingua.otf", 36, SDL_Color{ 255,255,255 }, scene, "Versus"));
		to->AddComponent(std::make_shared<TransformComponent>(260.f, 5.f));
		break;
	}
	scene.Add(to);

	// Level Game Object
	auto level = std::make_shared<GameObject>();
	auto grid = std::make_shared<std::vector<utils::Tile*>>();
	auto gridComp = std::make_shared<GridComponent>(35.f, 7, m_WindowWidth, grid, stoi(data.tileType.substr(4, 1)));
	level->AddComponent(gridComp);
	level->AddComponent(std::make_shared<GridRenderComponent>(level->GetComponent<GridComponent>()->GetVertices(), scene));
	scene.Add(level);

	// Fcn ptr to check if level has ended or not
	std::function<bool()> hasLevelEnded = std::bind(&GridComponent::HasLevelEnded, gridComp);

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

	// Observers:
	auto livesDisplay = std::make_shared<LivesDisplay>((UINT)InputManager::GetInstance().GetControllers().size());
	auto scoreDisplay = std::make_shared<ScoreDisplay>();
	auto resetObserver = std::make_shared<Resetter>();

	// --- QBERT CODE ---
	// Players + ScoreDisplayUI + LivesDisplayUI
	// Fcn ptr that returns QBert's position on the grid
	std::function<std::pair<int, int>()> getQBertPos;
	std::function<std::pair<int, int>()> getQBertPos2;
	// Give this function ptr to enemies so they can kill QBert when they come in contact
	std::function<void()> killFcn;
	std::function<void()> killFcn2;
	// Fcn ptr that can set QBert's teleport flag
	std::function<void(bool)> setTP;
	std::function<void(bool)> setTP2;

	std::shared_ptr<CoilyDefeatedDiscCommand> coilyCmd;
	std::shared_ptr<CatchSamSlickCommand> slickSamDefeatCmd;
	std::shared_ptr<RemainingDiscCommand> discCmd;

	auto inputResetter = std::make_shared<GameObject>();
	inputResetter->AddComponent(std::make_shared<InputResetComponent>(scene));
	
	for (UINT i{}; i < (UINT)InputManager::GetInstance().GetControllers().size(); ++i)
	{
		if (i == 1 && *m_GameMode == GameMode::versus)
			return;
		
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
		QBert->AddComponent(std::make_shared<PlayerComponent>(i));
		QBert->AddComponent(std::make_shared<ScoreComponent>());
		std::shared_ptr<HexTransformComponent> QBertTransformComp;
		switch(*m_GameMode)
		{
		case GameMode::coop:
			if (i == 0)
				QBertTransformComp = std::make_shared<HexTransformComponent>(grid, 6, -6);
			else
				QBertTransformComp = std::make_shared<HexTransformComponent>(grid, 6, 0);
			break;
		case GameMode::singleplayer:
			QBertTransformComp = std::make_shared<HexTransformComponent>(grid);
			break;
		}
		
		QBert->AddComponent(QBertTransformComp);
		if(i == 0)
			QBert->AddComponent(std::make_shared<GraphicsComponent2D>("../Data/QBert/Character/Right.png", scene));
		else
			QBert->AddComponent(std::make_shared<GraphicsComponent2D>("../Data/QBert/Character/Right2.png", scene));

		// Map inputs
		switch (data.levelName.back())
		{
		case '1':
			if (i == 0)
			{
				InputManager::GetInstance().AddCommand<MoveTopLeftCommand>(SDLK_LEFT,
					SDL_KEYUP, QBert);
				InputManager::GetInstance().AddCommand<MoveTopRightCommand>(SDLK_UP,
					SDL_KEYUP, QBert);
				InputManager::GetInstance().AddCommand<MoveDownLeftCommand>(SDLK_DOWN,
					SDL_KEYUP, QBert);
				InputManager::GetInstance().AddCommand<MoveDownRightCommand>(SDLK_RIGHT,
					SDL_KEYUP, QBert);
			}
			else
			{
				InputManager::GetInstance().AddCommand<MoveTopLeftCommand>(SDLK_q,
					SDL_KEYUP, QBert);
				InputManager::GetInstance().AddCommand<MoveTopRightCommand>(SDLK_z,
					SDL_KEYUP, QBert);
				InputManager::GetInstance().AddCommand<MoveDownLeftCommand>(SDLK_s,
					SDL_KEYUP, QBert);
				InputManager::GetInstance().AddCommand<MoveDownRightCommand>(SDLK_d,
					SDL_KEYUP, QBert);
			}

			InputManager::GetInstance().AddCommand<MoveTopLeftCommand>(ControllerKey(i, ControllerButton::ButtonLeft),
				XINPUT_KEYSTROKE_KEYUP, QBert);
			InputManager::GetInstance().AddCommand<MoveTopRightCommand>(ControllerKey(i, ControllerButton::ButtonUp),
				XINPUT_KEYSTROKE_KEYUP, QBert);
			InputManager::GetInstance().AddCommand<MoveDownLeftCommand>(ControllerKey(i, ControllerButton::ButtonDown),
				XINPUT_KEYSTROKE_KEYUP, QBert);
			InputManager::GetInstance().AddCommand<MoveDownRightCommand>(ControllerKey(i, ControllerButton::ButtonRight),
				XINPUT_KEYSTROKE_KEYUP, QBert);
			break;
		default:
			// Reset inputs
			if (i == 0)
			{
				inputResetter->GetComponent<InputResetComponent>()->AddCommand<MoveTopLeftCommand>(SDLK_LEFT,
					SDL_KEYUP, QBert);
				inputResetter->GetComponent<InputResetComponent>()->AddCommand<MoveTopRightCommand>(SDLK_UP,
					SDL_KEYUP, QBert);
				inputResetter->GetComponent<InputResetComponent>()->AddCommand<MoveDownLeftCommand>(SDLK_DOWN,
					SDL_KEYUP, QBert);
				inputResetter->GetComponent<InputResetComponent>()->AddCommand<MoveDownRightCommand>(SDLK_RIGHT,
					SDL_KEYUP, QBert);
			}
			else
			{
				inputResetter->GetComponent<InputResetComponent>()->AddCommand<MoveTopLeftCommand>(SDLK_q,
					SDL_KEYUP, QBert);
				inputResetter->GetComponent<InputResetComponent>()->AddCommand<MoveTopRightCommand>(SDLK_z,
					SDL_KEYUP, QBert);
				inputResetter->GetComponent<InputResetComponent>()->AddCommand<MoveDownLeftCommand>(SDLK_s,
					SDL_KEYUP, QBert);
				inputResetter->GetComponent<InputResetComponent>()->AddCommand<MoveDownRightCommand>(SDLK_d,
					SDL_KEYUP, QBert);
			}

			inputResetter->GetComponent<InputResetComponent>()->AddCommand<MoveTopLeftCommand>(ControllerKey(i, ControllerButton::ButtonLeft),
				XINPUT_KEYSTROKE_KEYUP, QBert);
			inputResetter->GetComponent<InputResetComponent>()->AddCommand<MoveTopRightCommand>(ControllerKey(i, ControllerButton::ButtonUp),
				XINPUT_KEYSTROKE_KEYUP, QBert);
			inputResetter->GetComponent<InputResetComponent>()->AddCommand<MoveDownLeftCommand>(ControllerKey(i, ControllerButton::ButtonDown),
				XINPUT_KEYSTROKE_KEYUP, QBert);
			inputResetter->GetComponent<InputResetComponent>()->AddCommand<MoveDownRightCommand>(ControllerKey(i, ControllerButton::ButtonRight),
				XINPUT_KEYSTROKE_KEYUP, QBert);
			break;
		}
		
		QBert->GetComponent<HealthComponent>()->GetSubject().AddObserver(livesDisplay);
		QBert->GetComponent<HealthComponent>()->GetSubject().AddObserver(resetObserver);
		QBert->GetComponent<ScoreComponent>()->GetSubject().AddObserver(scoreDisplay);
		scene.Add(QBert);

		// Set fcn pointers for external code to use
		switch(i)
		{
		case 0:
			getQBertPos = std::bind(&HexTransformComponent::GetRowCol, QBertTransformComp);
			killFcn = std::bind(&HealthComponent::Kill, &*healthComp);
			setTP = std::bind(&HexTransformComponent::SetTeleport, QBertTransformComp, std::placeholders::_1);
			coilyCmd = std::make_shared<CoilyDefeatedDiscCommand>(QBert);
			slickSamDefeatCmd = std::make_shared<CatchSamSlickCommand>(QBert);
			discCmd = std::make_shared<RemainingDiscCommand>(QBert);
			break;
		case 1:
			getQBertPos2 = std::bind(&HexTransformComponent::GetRowCol, QBertTransformComp);
			killFcn2 = std::bind(&HealthComponent::Kill, &*healthComp);
			setTP2 = std::bind(&HexTransformComponent::SetTeleport, QBertTransformComp, std::placeholders::_1);
			break;
		}
	}

	if(data.levelName.back() != '1')
		scene.Add(inputResetter);
	// --- QBERT CODE ---

	auto enemyResetter = std::make_shared<GameObject>();
	auto fullResetComp = std::make_shared<FullEnemyResetComponent>();
	enemyResetter->AddComponent(fullResetComp);
	
	// ----------- ENEMY CODE ---------------------------------
	if (std::find(data.enemies.begin(), data.enemies.end(), "Coily") != data.enemies.end())
	{
		// --- COILY ---
		/*auto coilyCmd = std::make_shared<CoilyDefeatedDiscCommand>(QBert);*/
		auto coily = std::make_shared<GameObject>();
		coily->AddComponent(std::make_shared<CoilyTransformComponent>(grid, getQBertPos, killFcn, coilyCmd, getQBertPos2, killFcn2));
		coily->AddComponent(std::make_shared<GraphicsComponent2D>("../Data/QBert/Enemies/Coily/Egg.png", scene));
		auto coilyResetComp = std::make_shared<CoilyResetComponent>();
		coily->AddComponent(coilyResetComp);
		coily->GetComponent<GraphicsComponent2D>()->SetVisibility(false);
		scene.Add(coily);

		// Coily's reset fcn ptr
		std::function<void()> coilyReset = std::bind(&CoilyResetComponent::Reset, coilyResetComp, coily);

		enemyResetter->GetComponent<FullEnemyResetComponent>()->AddResetter(coilyReset);
	}

	if (std::find(data.enemies.begin(), data.enemies.end(), "UggWrongway") != data.enemies.end())
	{
		// --- UGG & WRONGWAY ---
		auto wrongway = std::make_shared<GameObject>();
		wrongway->AddComponent(std::make_shared<UggWrongWayTransformComponent>(grid, getQBertPos, killFcn,
			UggWrongWayTransformComponent::EntityType::wrongway, getQBertPos2, killFcn2));
		wrongway->AddComponent(std::make_shared<GraphicsComponent2D>("../Data/QBert/Enemies/Wrongway/Wrongway.png", scene));
		auto wrongwayResetComp = std::make_shared<UggWrongwayResetComponent>();
		wrongway->AddComponent(wrongwayResetComp);
		wrongway->GetComponent<GraphicsComponent2D>()->SetVisibility(false);
		scene.Add(wrongway);
		// Wrongway's reset fcn ptr
		std::function<void()> wrongwayReset = std::bind(&UggWrongwayResetComponent::Reset, wrongwayResetComp, wrongway);

		auto ugg = std::make_shared<GameObject>();
		ugg->AddComponent(std::make_shared<UggWrongWayTransformComponent>(grid, getQBertPos, killFcn,
			UggWrongWayTransformComponent::EntityType::ugg, getQBertPos2, killFcn2));
		ugg->AddComponent(std::make_shared<GraphicsComponent2D>("../Data/QBert/Enemies/Ugg/Ugg.png", scene));
		auto uggResetComp = std::make_shared<UggWrongwayResetComponent>();
		ugg->AddComponent(uggResetComp);
		ugg->GetComponent<GraphicsComponent2D>()->SetVisibility(false);
		scene.Add(ugg);
		// Ugg's reset fcn ptr
		std::function<void()> uggReset = std::bind(&UggWrongwayResetComponent::Reset, uggResetComp, ugg);

		enemyResetter->GetComponent<FullEnemyResetComponent>()->AddResetter(wrongwayReset);
		enemyResetter->GetComponent<FullEnemyResetComponent>()->AddResetter(uggReset);
	}

	if (std::find(data.enemies.begin(), data.enemies.end(), "SlickSam") != data.enemies.end())
	{
		// --- SLICK & SAM ---
		/*auto slickSamDefeatCmd = std::make_shared<CatchSamSlickCommand>(QBert);*/
		auto slick = std::make_shared<GameObject>();
		slick->AddComponent(std::make_shared<SlickSamTransformComponent>(grid, getQBertPos, SlickSamTransformComponent::EntityType::slick, slickSamDefeatCmd,
			getQBertPos2));
		slick->AddComponent(std::make_shared<GraphicsComponent2D>("../Data/QBert/Enemies/Slick/Slick.png", scene));
		auto slickResetComp = std::make_shared<SlickSamResetComponent>();
		slick->AddComponent(slickResetComp);
		slick->GetComponent<GraphicsComponent2D>()->SetVisibility(false);
		scene.Add(slick);

		// Slick's reset fcn ptr
		std::function<void()> slickReset = std::bind(&SlickSamResetComponent::Reset, slickResetComp, slick);

		auto sam = std::make_shared<GameObject>();
		sam->AddComponent(std::make_shared<SlickSamTransformComponent>(grid, getQBertPos, SlickSamTransformComponent::EntityType::sam, slickSamDefeatCmd,
			getQBertPos2));
		sam->AddComponent(std::make_shared<GraphicsComponent2D>("../Data/QBert/Enemies/Sam/Sam.png", scene));
		auto samResetComp = std::make_shared<SlickSamResetComponent>();
		sam->AddComponent(samResetComp);
		sam->GetComponent<GraphicsComponent2D>()->SetVisibility(false);
		scene.Add(sam);

		// Slick's reset fcn ptr
		std::function<void()> samReset = std::bind(&SlickSamResetComponent::Reset, samResetComp, sam);

		enemyResetter->GetComponent<FullEnemyResetComponent>()->AddResetter(slickReset);
		enemyResetter->GetComponent<FullEnemyResetComponent>()->AddResetter(samReset);
	}
	// ----------- ENEMY CODE ---------------------------------

	// ----------- ENEMY RESETTER ------------------
	std::function<void()> resetAllFcn = std::bind(&FullEnemyResetComponent::ResetAll, fullResetComp);
	// Add the ResetAll method to the resetter observer
	resetObserver->AddData(resetAllFcn);
	scene.Add(enemyResetter);
	// ----------- ENEMY RESETTER ------------------

	// --- DISCS ---
	/*auto discCmd = std::make_shared<RemainingDiscCommand>(QBert);*/
	auto leftDisc = std::make_shared<GameObject>();
	leftDisc->AddComponent(std::make_shared<DiscTransformComponent>(grid, getQBertPos, setTP, hasLevelEnded, discCmd, true, getQBertPos2, setTP2));
	leftDisc->AddComponent(std::make_shared<GraphicsComponent2D>("../Data/QBert/Objects/Disc.png", scene));
	scene.Add(leftDisc);

	auto rightDisc = std::make_shared<GameObject>();
	rightDisc->AddComponent(std::make_shared<DiscTransformComponent>(grid, getQBertPos, setTP, hasLevelEnded, discCmd, false, getQBertPos2, setTP2));
	rightDisc->AddComponent(std::make_shared<GraphicsComponent2D>("../Data/QBert/Objects/Disc.png", scene));
	scene.Add(rightDisc);
	// --- DISCS ---
}

void LevelManager::ReadJSON(const std::wstring& filePath, rapidjson::Document& doc)
{
	FILE* fp = nullptr;
	_wfopen_s(&fp, filePath.c_str(), L"rb");

	if (fp)
	{
		fseek(fp, 0, SEEK_END);

		fseek(fp, 0, SEEK_SET);
		char readBuffer[65'536];
		rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
		doc.ParseStream(is);

		fclose(fp);
	}
}