#include "MiniginPCH.h"
#include "SceneManager.h"

#include <algorithm>
#include <SDL.h>


#include "Scene.h"
#include "ServiceLocator.h"

void dae::SceneManager::Update(float elapsedSec)
{
	if(m_CanDelete)
	{
		auto mainMenu = m_Scenes.front();
		
		m_Scenes.clear();
		m_Scenes.push_back(mainMenu);
		mainMenu->Activate();
		m_CanDelete = false;
		ServiceLocator::GetAudioService()->PlaySound("../Data/QBert/Sounds/tune.wav", SDL_MIX_MAXVOLUME);
	}
	
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

void dae::SceneManager::MarkForDeletion()
{
	m_CanDelete = true;
}