#pragma once
#include <functional>

#include <map>

class TransformComponent;
class Component;
class CalculationComponent;
class InputComponent;
class GraphicsComponent2D;
class MovementComponent;
namespace dae
{
	class Texture2D;
	class GameObject final
	{
	public:
		void Update(float elapsedSec);

		static unsigned int GetId();

		template<typename T>
		const std::shared_ptr<T> GetComponent() const
		{
			for (auto& comp : m_pComponents)
			{
				if (std::dynamic_pointer_cast<T>(comp))
					return std::dynamic_pointer_cast<T>(comp);
			}
			return nullptr;
		}

		void AddComponent(std::shared_ptr<Component> comp);
		
		GameObject();
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		static unsigned int m_IdCounter;

		// Components
		std::vector<std::shared_ptr<Component>> m_pComponents;
	};
}
