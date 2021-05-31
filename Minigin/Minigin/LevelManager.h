#pragma once
#include "GameObject.h"
#include "rapidjson/document.h"

struct LevelData
{
	std::string levelName;
	std::string tileType;
	std::vector<std::string> enemies;
};

class LevelManager final
{
public:
	enum class GameMode
	{
		singleplayer,
		coop,
		versus
	};
	
	LevelManager(int windowWidth);
	void LoadMainMenu();
	void LoadLevel(const std::wstring& fileName);
	void ReadJSON(const std::wstring& fileName, rapidjson::Document& doc) const;
	void SetUpLevel(const LevelData& data);
private:
	int m_WindowWidth;
	std::shared_ptr<GameMode> m_pGameMode;
};
