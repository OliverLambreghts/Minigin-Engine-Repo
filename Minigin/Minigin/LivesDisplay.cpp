#include "MiniginPCH.h"
#include "LivesDisplay.h"

#include "PlayerComponent.h"

float LivesDisplay::m_Y = 450.f;

LivesDisplay::LivesDisplay(dae::Scene& scene, UINT players)
	: m_Lives(players, 10)
{
	for (UINT i{}; i < players; ++i)
	{
		m_TextComponents.push_back(std::make_shared<TextComponent>("Lingua.otf", 16, SDL_Color{ 0, 255, 0 }, scene));
		Transform pos{};
		pos.SetPosition(m_X, m_Y, 0);
		m_TextComponents[i]->SetText("Player " + std::to_string(i + 1) + " Lives: " + std::to_string(m_StartLives));
		m_TextComponents[i]->SetPos(pos);
		m_Y -= 20.f;
		m_TextComponents[i]->Update();
	}

	std::function<void() > wrapper = std::bind(&LivesDisplay::Render, this);
	scene.AddRenderData(wrapper);
}

void LivesDisplay::OnNotify(const dae::GameObject& obj, Message message)
{
	switch (message)
	{
	case Message::PlayerDied:
		UINT id = obj.GetComponent<PlayerComponent>()->GetID();
		--m_Lives[id];
		m_TextComponents[id]->SetText("Player " + std::to_string(id + 1) + " Lives: " + std::to_string(m_Lives[id]));
		m_TextComponents[id]->Update();
		break;
	}
}

void LivesDisplay::Render()
{
	for (auto& comp : m_TextComponents)
	{
		comp->Render();
	}
}