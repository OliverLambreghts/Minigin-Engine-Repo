#pragma once
#include "Observer.h"
#include "TextComponent.h"

class LivesDisplay : public Observer
{
public:
	LivesDisplay(dae::Scene& scene, UINT players);
	
	virtual void OnNotify(const dae::GameObject& obj, Message message) override;

	void Render();
private:
	std::vector<int> m_Lives;
	int m_StartLives = 10;

	std::vector<std::shared_ptr<TextComponent>> m_TextComponents;

	static float m_Y;
	float m_X = 500.f;
};