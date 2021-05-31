#include "MiniginPCH.h"
#include "GraphicsComponent2D.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TransformComponent.h"

GraphicsComponent2D::GraphicsComponent2D(const std::string& fileName, Scene& scene)
	: m_Transform{},
	m_IsVisible{ true }
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(fileName);
	std::function<void()> renderWrapper = std::bind(&GraphicsComponent2D::Render, this);
	scene.AddRenderData(renderWrapper);
}

void GraphicsComponent2D::Update(float, GameObject& obj)
{
	const auto pos = obj.GetComponent<TransformComponent>()->GetPos();
	if (m_Transform.GetPosition() != pos.GetPosition())
		m_Transform = pos;
}

void GraphicsComponent2D::Render() const
{
	if (m_pTexture && m_IsVisible)
		Renderer::GetInstance().RenderTexture(*m_pTexture, m_Transform.GetPosition().x, m_Transform.GetPosition().y);
}

void GraphicsComponent2D::SetVisibility(bool isVisible)
{
	m_IsVisible = isVisible;
}

void GraphicsComponent2D::ChangeTexture(const std::string& filePath)
{
	m_pTexture.reset();
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filePath);
}