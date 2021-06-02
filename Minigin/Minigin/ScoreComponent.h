#pragma once
#include "GameplayComponent.h"
#include "Subject.h"
#include "utils.h"
#include <queue>

class ScoreComponent final : public GameplayComponent
{
public:
	explicit ScoreComponent(std::shared_ptr<std::vector<utils::Tile*>>& tiles);
	virtual ~ScoreComponent() = default;
	ScoreComponent(const ScoreComponent& other) = delete;
	ScoreComponent(ScoreComponent&& other) = delete;
	void operator=(const ScoreComponent& rhs) = delete;
	void operator=(const ScoreComponent&& rhs) = delete;

	virtual void Update(float elapsedSec, GameObject& obj) override;

	void SetScoreEvent(Message message);

	int GetScore() const;

	Subject& GetSubject();
private:
	void SaveToFile() const;
	
	Message m_ScoreEvent;
	int m_Score;
	std::shared_ptr<std::vector<utils::Tile*>> m_pTiles;
	Subject m_Subject;
	std::queue<Message> m_MessageQueue;
};
