#pragma once
#include <functional>

#include "GameObject.h"
#include "SceneManager.h"
#include <map>

namespace dae
{
	class SceneObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(const std::shared_ptr<GameObject>& object);
		void AddRenderData(std::function<void()> fcnPtr);

		void Update(float elapsedSec);
		void Render() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector < std::shared_ptr<GameObject>> m_Objects{};
		std::map<unsigned int, std::function<void()>> m_RenderData;

		static unsigned int m_IdCounter;
	};

}
