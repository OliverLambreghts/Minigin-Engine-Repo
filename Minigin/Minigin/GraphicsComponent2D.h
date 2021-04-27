#pragma once
#include "GameObject.h"
#include "GraphicsComponent.h"
#include "Scene.h"
#include "Transform.h"

using namespace dae;
class GraphicsComponent2D : public GraphicsComponent
{
public:
	GraphicsComponent2D(std::string fileName, Scene& scene);
	GraphicsComponent2D() = default;
	virtual ~GraphicsComponent2D() = default;
	GraphicsComponent2D(const GraphicsComponent2D& other) = delete;
	GraphicsComponent2D(GraphicsComponent2D&& other) = delete;
	void operator=(const GraphicsComponent2D& rhs) = delete;
	void operator=(const GraphicsComponent2D&& rhs) = delete;
	
	virtual void Update(float elapsedSec, GameObject& obj) override;

	void Render() const;

	void SetVisibility(bool isVisible);

	void ChangeTexture(const std::string& filePath);
protected:
	std::shared_ptr<Texture2D> m_Texture;
	Transform m_Transform;
	bool m_IsVisible;
};