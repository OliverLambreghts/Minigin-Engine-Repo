#pragma once
#include "Observer.h"

class ScoreDisplay : public Observer
{
public:
	ScoreDisplay();

	virtual void OnNotify(const dae::GameObject& obj, Message message) override;

	void AddData(dae::GameObject& obj);
private:
	std::vector<std::function<void(std::string) >> m_SetMethods;
	std::vector<std::function<void()>> m_UpdateMethods;
	
	int m_Players;
	static float m_Y;
	float m_X = 10.f;
};