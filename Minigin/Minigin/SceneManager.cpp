#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(float elapsedSec)
{
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
		if(canActivate)
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