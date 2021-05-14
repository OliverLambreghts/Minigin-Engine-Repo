#include "MiniginPCH.h"
#include "UIGameModeButton.h"
#include "imgui.h"
#include "InputManager.h"
#include "SceneManager.h"

UIGameModeButton::UIGameModeButton(std::string name, bool staysActive, std::shared_ptr<LevelManager::GameMode> pGameMode, LevelManager::GameMode gameMode,
                                   std::function<void(const std::wstring&)> loadLevel)
	: m_Name{ name },
	m_StaysActive{ staysActive },
	m_pGameMode{ pGameMode },
	m_GameMode{ gameMode },
	m_LoadLevel{ loadLevel }
{

}

void UIGameModeButton::Update()
{

}

void UIGameModeButton::Render()
{
	if (ImGui::Button(m_Name.c_str()))
	{
		switch(m_GameMode)
		{
		case LevelManager::GameMode::singleplayer:
			dae::InputManager::GetInstance().AddController();
			break;
		default:
			dae::InputManager::GetInstance().AddController();
			dae::InputManager::GetInstance().AddController();
			break;
		}
		
		m_IsActive = !m_IsActive;
		*m_pGameMode = m_GameMode;
		m_LoadLevel(L"../Data/QBert/Levels/Level1.JSON");
		m_LoadLevel(L"../Data/QBert/Levels/Level2.JSON");
		m_LoadLevel(L"../Data/QBert/Levels/Level3.JSON");
		dae::SceneManager::GetInstance().ActivateNextScene();
	}
}

void UIGameModeButton::SetName(std::string name)
{
	m_Name = name;
}

bool UIGameModeButton::IsActive()
{
	if (!m_StaysActive && m_IsActive)
	{
		m_IsActive = false;
		return true;
	}
	return m_IsActive;
}