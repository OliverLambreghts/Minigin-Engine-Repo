#pragma once
#include "GameObject.h"
#include "rapidjson/document.h"

struct LevelData
{
	std::string levelName;
	std::string tileType;
	std::vector<std::string> enemies;
};

class LevelManager
{
public:
	LevelManager(int windowWidth);
	void LoadLevel(const std::wstring& fileName);
	void ReadJSON(const std::wstring& fileName, rapidjson::Document& doc);
	void SetUpLevel(const LevelData& data);
private:
	int m_WindowWidth;
};
