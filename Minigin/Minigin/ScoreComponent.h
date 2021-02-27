#pragma once
#include "GameplayComponent.h"

class ScoreComponent : public GameplayComponent
{
public:
	ScoreComponent() = default;
	virtual ~ScoreComponent() = default;
	ScoreComponent(const ScoreComponent& other) = delete;
	ScoreComponent(ScoreComponent&& other) = delete;
	void operator=(const ScoreComponent& rhs) = delete;
	void operator=(const ScoreComponent&& rhs) = delete;

	virtual void Update(float elapsedSec, GameObject& obj) override;

	void SetScoreEvent(Message message);

	int GetScore() const;
private:
	Message m_ScoreEvent;
	int m_Score;
};