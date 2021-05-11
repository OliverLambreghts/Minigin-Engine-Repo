#include "MiniginPCH.h"
#include "LevelManager.h"


#include "GridComponent.h"
#include "utils.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include <string>

LevelManager::LevelManager(int windowWidth)
	: m_WindowWidth{ windowWidth }
{

}

void LevelManager::LoadLevel(const std::wstring& filePath)
{
	auto newLevel = std::make_shared<dae::GameObject>();
	rapidjson::Document jsonDoc;
	ReadJSON(filePath, jsonDoc);

	std::string tileType = jsonDoc["tileType"].GetString();
	auto grid = std::make_shared<std::vector<utils::Tile*>>();
	int tileNr = stoi(tileType.substr(4, 1));
	auto gridComp = std::make_shared<GridComponent>(35.f, 7, m_WindowWidth, grid, tileNr);

	
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