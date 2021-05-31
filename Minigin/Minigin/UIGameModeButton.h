#pragma once
#include "UIElement.h"
#include <string>

#include "LevelManager.h"

class UIGameModeButton final : public UIElement
{
public:
	UIGameModeButton(const std::string& name, bool staysActive, std::shared_ptr<LevelManager::GameMode> pGameMode, LevelManager::GameMode gameMode,
		std::function<void(const std::wstring&)> loadLevel);

	virtual ~UIGameModeButton() = default;
	UIGameModeButton(const UIGameModeButton& other) = delete;
	UIGameModeButton(UIGameModeButton&& other) = delete;
	void operator=(const UIGameModeButton& rhs) = delete;
	void operator=(const UIGameModeButton&& rhs) = delete;

	virtual void Update() override;

	virtual void Render() override;

	void SetName(std::string name);

	virtual bool IsActive() override;
private:
	std::string m_Name;
	bool m_IsActive = false, m_StaysActive;
	std::shared_ptr<LevelManager::GameMode> m_pGameMode;
	LevelManager::GameMode m_GameMode;
	std::function<void(const std::wstring&)> m_LoadLevel;
};
