#include "MiniginPCH.h"
#include "TextComponent.h"
#include "SDL.h"
#include <SDL_ttf.h>

#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"
#include "ResourceManager.h"
#include "TransformComponent.h"

TextComponent::TextComponent(std::string font, unsigned int fontSize, SDL_Color color, std::string text, Scene& scene, GameObject& obj)
	: m_Text{ text },
	m_Color{ color },
	m_NeedsUpdate{ true },
	m_Font{}
{
	m_Font = ResourceManager::GetInstance().LoadFont(font, fontSize);
	const std::function<void()> wrapper = std::bind(&TextComponent::Render, this);
	scene.AddRenderData(wrapper);
	const std::function<void(float, GameObject&)> updateWrapper = std::bind(&TextComponent::Update, this, std::placeholders::_1, std::placeholders::_2);
	obj.AddUpdateData(updateWrapper);
}

void TextComponent::Update(float, GameObject& obj)
{	
	if (m_NeedsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_Texture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
	const auto pos = dynamic_cast<TransformComponent*>(obj.GetComponent("transform").get())->GetPos();
	if (m_Transform.GetPosition() != pos.GetPosition())
		m_Transform = pos;
}

void TextComponent::SetText(std::string newText)
{
	m_Text = newText;
	m_NeedsUpdate = true;
}