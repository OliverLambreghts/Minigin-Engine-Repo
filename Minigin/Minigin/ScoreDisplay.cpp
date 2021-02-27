#include "MiniginPCH.h"
#include "ScoreDisplay.h"

#include "PlayerComponent.h"
#include "ScoreComponent.h"

float ScoreDisplay::m_Y = 450.f;

ScoreDisplay::ScoreDisplay(dae::Scene& scene, UINT players)
{
	for (UINT i{}; i < players; ++i)
	{
		m_TextComponents.push_back(std::make_shared<TextComponent>("Lingua.otf", 16, SDL_Color{ 0, 255, 0 }, scene));
		Transform pos{};
		pos.SetPosition(m_X, m_Y, 0);
		m_TextComponents[i]->SetText("Player " + std::to_string(i + 1) + " Score: 0");
		m_TextComponents[i]->SetPos(pos);
		m_Y -= 20.f;
		m_TextComponents[i]->Update();
	}

	std::function<void() > wrapper = std::bind(&ScoreDisplay::Render, this);
	scene.AddRenderData(wrapper);
}

void ScoreDisplay::OnNotify(const dae::GameObject& obj, Message message)
{
	if (message > Message::CaughtSlickOrSam || message == Message::DoNothing)
		return;

	UINT id = obj.GetComponent<PlayerComponent>()->GetID();
	int score = obj.GetComponent<ScoreComponent>()->GetScore();
	m_TextComponents[id]->SetText("Player " + std::to_string(id + 1) + " Score: " + std::to_string(score));
	m_TextComponents[id]->Update();
}

void ScoreDisplay::Render()
{
	for (auto& comp : m_TextComponents)
	{
		comp->Render();
	}
}