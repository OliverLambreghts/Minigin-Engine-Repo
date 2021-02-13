#include "MiniginPCH.h"
#include "GraphicsComponent.h"

#include <SDL_render.h>

#include "Renderer.h"
#include "ResourceManager.h"
#include "TransformComponent.h"

GraphicsComponent::GraphicsComponent(std::string fileName, Scene& scene, GameObject& obj)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(fileName);
	//auto fcn = &Render;
	const std::function<void()> renderWrapper = std::bind(&GraphicsComponent::Render, this);
	scene.AddRenderData(renderWrapper);
	const std::function<void(float, GameObject&)> updateWrapper = std::bind(&GraphicsComponent::Update, this, std::placeholders::_1, std::placeholders::_2);
	obj.AddUpdateData(updateWrapper);
}

void GraphicsComponent::Update(float, GameObject& obj)
{
	const auto pos = dynamic_cast<TransformComponent*>(obj.GetComponent("transform").get())->GetPos();
	if(m_Transform.GetPosition() != pos.GetPosition())
		m_Transform = pos;
}

void GraphicsComponent::Render() const
{
	if(m_Texture)
		Renderer::GetInstance().RenderTexture(*m_Texture, m_Transform.GetPosition().x, m_Transform.GetPosition().y);
}