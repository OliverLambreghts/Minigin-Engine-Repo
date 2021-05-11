#pragma once
#include "GameObject.h"
#include "rapidjson/document.h"

class LevelManager
{
public:
	LevelManager(int windowWidth);
	void LoadLevel(const std::wstring& fileName);
	void ReadJSON(const std::wstring& fileName, rapidjson::Document& doc);
private:
	std::vector<std::shared_ptr<dae::GameObject>> m_Levels;
	int m_WindowWidth;
};
