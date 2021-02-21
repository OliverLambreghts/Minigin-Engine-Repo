#include "MiniginPCH.h"
#include "DataManager.h"

void DataManager::Update()
{
	for (auto& data : m_Data)
	{
		data->Update();
	}
}