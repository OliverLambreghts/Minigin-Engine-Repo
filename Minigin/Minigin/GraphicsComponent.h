#pragma once
#include "GameObject.h"
#include "Component.h"
#include "Scene.h"
#include "Transform.h"

using namespace dae;
class GraphicsComponent : public Component
{
public:
	GraphicsComponent(std::string fileName, Scene& scene, GameObject& obj);
	GraphicsComponent() = default;
	virtual ~GraphicsComponent() = default;
	GraphicsComponent(const GraphicsComponent& other) = delete;
	GraphicsComponent(GraphicsComponent&& other) = delete;
	void operator=(const GraphicsComponent& rhs) = delete;
	void operator=(const GraphicsComponent&& rhs) = delete;
	
	virtual void Update(float elapsedSec, GameObject& obj);

	void Render() const;
protected:
	std::shared_ptr<Texture2D> m_Texture;
	Transform m_Transform;
};