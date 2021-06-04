#include "MiniginPCH.h"
#include "ScoreDisplay.h"

#include "PlayerComponent.h"
#include "ScoreComponent.h"
#include "TextComponent.h"
#include "Transform.h"

float ScoreDisplay::m_Y = 450.f;
std::vector<int> ScoreDisplay::m_Scores;

ScoreDisplay::ScoreDisplay(UINT players)
	: m_Players{ 0 }
{
	m_Scores.clear();
	if (m_Scores.size() == players) return;
	for (UINT i{}; i < players; ++i)
		m_Scores.push_back(0);
}

void ScoreDisplay::AddData(GameObject& obj)
{
	Transform pos{};
	pos.SetPosition(m_X, m_Y, 0);
	++m_Players;
	obj.GetComponent<TextComponent>()->SetText("Player " + std::to_string(m_Players) + " Score: ");
	obj.GetComponent<TextComponent>()->SetPos(pos);
	obj.GetComponent<TextComponent>()->ObsUpdate();
	m_SetMethods.push_back(std::bind(&TextComponent::SetText, obj.GetComponent<TextComponent>(), std::placeholders::_1));
	m_UpdateMethods.push_back(std::bind(&TextComponent::ObsUpdate, obj.GetComponent<TextComponent>()));
	const float yOffset = 20.f;
	m_Y -= yOffset;
	const float yThreshold = 430.f;
	if (m_Y < yThreshold)
		m_Y = 450.f;
}

void ScoreDisplay::OnNotify(const dae::GameObject& obj, Message message)
{
	if (message != Message::UpdateMsg && message > Message::CaughtSlickOrSam || message == Message::DoNothing)
		return;

	switch (message)
	{
	case Message::ColorChange:
		m_Scores[obj.GetComponent<PlayerComponent>()->GetID()] += 25;
		break;
	case Message::CoilyDefeatedDisc:
		m_Scores[obj.GetComponent<PlayerComponent>()->GetID()] += 500;
		break;
	case Message::RemainingDisc:
		m_Scores[obj.GetComponent<PlayerComponent>()->GetID()] += 50;
		break;
	case Message::CaughtSlickOrSam:
		m_Scores[obj.GetComponent<PlayerComponent>()->GetID()] += 300;
		break;
	}

	UINT id = obj.GetComponent<PlayerComponent>()->GetID();
	m_SetMethods[id]("Player " + std::to_string(id + 1) + " Score: " + std::to_string(m_Scores[obj.GetComponent<PlayerComponent>()->GetID()]));
	m_UpdateMethods[id]();
}