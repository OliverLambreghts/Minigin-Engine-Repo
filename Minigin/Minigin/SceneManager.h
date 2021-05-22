#pragma once
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void Update(float elapsedSec);
		void Render();

		void MarkForDeletion();
		void DeactivateAllScenes();
		void ActivateNextScene();
		void ActivateFirstScene();
		void ClearScenes();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		bool m_CanDelete = false;
	};
}
