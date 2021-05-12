#include "MiniginPCH.h"
#include "ScoreDisplay.h"

#include "PlayerComponent.h"
#include "ScoreComponent.h"
#include "TextComponent.h"
#include "Transform.h"

float ScoreDisplay::m_Y = 450.f;

ScoreDisplay::ScoreDisplay()
	: m_Players{0}
{
}

void ScoreDisplay::AddData(GameObject& obj)
{
	Transform pos{};
	pos.SetPosition(m_X, m_Y, 0);
	++m_Players;
	obj.GetComponent<TextComponent>()->SetText("Player " + std::to_string(m_Players) + " Score: 0");
	obj.GetComponent<TextComponent>()->SetPos(pos);
	obj.GetComponent<TextComponent>()->ObsUpdate();
	m_SetMethods.push_back(std::bind(&TextComponent::SetText, obj.GetComponent<TextComponent>(), std::placeholders::_1));
	m_UpdateMethods.push_back(std::bind(&TextComponent::ObsUpdate, obj.GetComponent<TextComponent>()));
	m_Y -= 20.f;
}

void ScoreDisplay::OnNotify(const dae::GameObject& obj, Message message)
{
	if (message > Message::CaughtSlickOrSam || message == Message::DoNothing)
		return;
	
	UINT id = obj.GetComponent<PlayerComponent>()->GetID();
	int score = obj.GetComponent<ScoreComponent>()->GetScore();
	m_SetMethods[id]("Player " + std::to_string(id + 1) + " Score: " + std::to_string(score));
	m_UpdateMethods[id]();
}