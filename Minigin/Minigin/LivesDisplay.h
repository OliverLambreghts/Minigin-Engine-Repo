#pragma once
#include "Observer.h"

class LivesDisplay : public Observer
{
public:
	LivesDisplay(UINT players);
	
	virtual void OnNotify(const dae::GameObject& obj, Message message) override;

	void AddData(dae::GameObject& obj);

private:
	std::vector<std::function<void(std::string) >> m_SetMethods;
	std::vector<std::function<void()>> m_UpdateMethods;
	
	std::vector<int> m_Lives;
	int m_StartLives = 3;
	int m_Players;

	static float m_Y;
	float m_X = 500.f;
};