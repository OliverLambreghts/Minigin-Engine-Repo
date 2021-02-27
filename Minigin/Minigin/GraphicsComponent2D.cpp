#include "MiniginPCH.h"
#include "GraphicsComponent2D.h"

#include "Renderer.h"
#include "ResourceManager.h"
#include "TransformComponent.h"

GraphicsComponent2D::GraphicsComponent2D(std::string fileName, Scene& scene)
	: m_Transform{}
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(fileName);
	std::function<void()> renderWrapper = std::bind(&GraphicsComponent2D::Render, this);
	scene.AddRenderData(renderWrapper);
}

void GraphicsComponent2D::Update(float, GameObject& obj)
{
	const auto pos = obj.GetComponent<TransformComponent>()->GetPos();
	if(m_Transform.GetPosition() != pos.GetPosition())
		m_Transform = pos;
}

void GraphicsComponent2D::Render() const
{
	if(m_Texture)
		Renderer::GetInstance().RenderTexture(*m_Texture, m_Transform.GetPosition().x, m_Transform.GetPosition().y);
}