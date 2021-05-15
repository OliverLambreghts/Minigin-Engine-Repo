#include "MiniginPCH.h"
#include "SceneManager.h"

#include <algorithm>

#include "Scene.h"

void dae::SceneManager::Update(float elapsedSec)
{
	if (m_Scenes.size() > 4)
		m_Scenes.erase(m_Scenes.begin(), m_Scenes.begin() + 4);
	
	for (auto& scene : m_Scenes)
	{
		if (scene->IsActive())
		{
			scene->Update(elapsedSec);
			break;
		}
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		if (scene->IsActive())
		{
			scene->Render();
			break;
		}
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}

void dae::SceneManager::ActivateNextScene()
{
	bool canActivate{ false };
	for (auto& scene : m_Scenes)
	{
		if (canActivate)
		{
			scene->Activate();
			break;
		}

		if (scene->IsActive() && !canActivate)
		{
			scene->Deactivate();
			canActivate = true;
		}
	}
}

void dae::SceneManager::ActivateFirstScene()
{
	m_Scenes.front()->Activate();
}

void dae::SceneManager::ClearScenes()
{
	m_Scenes.clear();
}

void dae::SceneManager::DeactivateAllScenes()
{
	std::for_each(m_Scenes.begin(), m_Scenes.end(), [](std::shared_ptr<Scene>& scene) {scene->Deactivate(); });
}