#include "MiniginPCH.h"
#include "ScoreComponent.h"

#include <algorithm>
#include <fstream>

ScoreComponent::ScoreComponent(std::shared_ptr<std::vector<utils::Tile*>>& tiles)
	: m_pTiles{ tiles },
	m_Score {},
	m_ScoreEvent{},
	m_Subject{},
	m_MessageQueue{}
{

}

void ScoreComponent::Update(float, GameObject& obj)
{
	if (std::all_of(m_pTiles->begin(), m_pTiles->end(), [](utils::Tile* tile) {return tile->IsActive(); }))
		SaveToFile();

	if (!m_MessageQueue.empty())
	{
		m_ScoreEvent = m_MessageQueue.front();
		m_MessageQueue.pop();
	}

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
	m_MessageQueue.push(message);
}

int ScoreComponent::GetScore() const
{
	return m_Score;
}

Subject& ScoreComponent::GetSubject()
{
	return m_Subject;
}

void ScoreComponent::SaveToFile() const
{
	std::ofstream file{ "HighScores.txt" };
	file << m_Score << '\n';
	file.close();
}