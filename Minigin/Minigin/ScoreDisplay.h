#pragma once
#include "Observer.h"

class ScoreDisplay final : public Observer
{
public:
	explicit ScoreDisplay(UINT players);

	virtual ~ScoreDisplay() = default;
	ScoreDisplay(const ScoreDisplay& other) = delete;
	ScoreDisplay(ScoreDisplay&& other) = delete;
	void operator=(const ScoreDisplay& rhs) = delete;
	void operator=(const ScoreDisplay&& rhs) = delete;
	
	virtual void OnNotify(const dae::GameObject& obj, Message message) override;

	void AddData(dae::GameObject& obj);
private:
	std::vector<std::function<void(std::string) >> m_SetMethods;
	std::vector<std::function<void()>> m_UpdateMethods;

	static std::vector<int> m_Scores;
	int m_Players;
	static float m_Y;
	float m_X = 10.f;
};