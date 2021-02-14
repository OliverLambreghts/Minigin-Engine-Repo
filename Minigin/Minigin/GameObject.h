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
		const std::shared_ptr<Component> GetComponent(std::string name) const;

		void SetPos(float x, float y);

		void AddComponent(std::string, std::shared_ptr<Component> comp);
		//void AddUpdateData(std::function<void(float, GameObject&)> fcnPtr);
		
		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		static unsigned int m_IdCounter;

		// Components
		std::map<std::string, std::shared_ptr<Component>> m_pComponents;
		//std::vector < std::function<void(float, GameObject&) >> m_UpdateData;
	};
}
