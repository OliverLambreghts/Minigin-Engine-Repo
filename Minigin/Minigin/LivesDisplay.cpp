#include "MiniginPCH.h"
#include "LivesDisplay.h"

#include "PlayerComponent.h"
#include "TextComponent.h"
#include "Transform.h"

float LivesDisplay::m_Y = 450.f;

LivesDisplay::LivesDisplay(UINT players)
	: m_Lives(players, 3),
	m_Players{}
{
}

void LivesDisplay::AddData(GameObject& obj)
{
	Transform pos{};
	pos.SetPosition(m_X, m_Y, 0);
	++m_Players;
	obj.GetComponent<TextComponent>()->SetText("Player " + std::to_string(m_Players)
		+ " Lives: " + std::to_string(m_StartLives));
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

void LivesDisplay::OnNotify(const dae::GameObject& obj, Message message)
{
	switch (message)
	{
	case Message::PlayerDied:
		UINT id = obj.GetComponent<PlayerComponent>()->GetID();
		--m_Lives[id];
		m_SetMethods[id]("Player " + std::to_string(id + 1) + " Lives: " + std::to_string(m_Lives[id]));
		m_UpdateMethods[id]();
		break;
	}
}