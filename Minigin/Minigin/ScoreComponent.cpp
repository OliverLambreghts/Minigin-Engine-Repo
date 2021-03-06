#include "MiniginPCH.h"
#include "ScoreComponent.h"

void ScoreComponent::Update(float , GameObject& obj)
{
	switch (m_ScoreEvent)
	{
	case Message::ColorChange:
		m_Score += 25;
		break;
	case Message::CoilyDefeatedDisc:
		m_Score += 500;
		break;
	case Message::RemainingDisc:
		m_Score += 50;
		break;
	case Message::CaughtSlickOrSam:
		m_Score += 300;
		break;
	}

	m_Subject.Notify(obj, m_ScoreEvent);
	m_ScoreEvent = Message::DoNothing;
}

void ScoreComponent::SetScoreEvent(Message message)
{
	m_ScoreEvent = message;
}

int ScoreComponent::GetScore() const
{
	return m_Score;
}

Subject& ScoreComponent::GetSubject()
{
	return m_Subject;
}