#pragma once
#include "Observer.h"
#include "TextComponent.h"

class ScoreDisplay : public Observer
{
public:
	ScoreDisplay(dae::Scene& scene, UINT players);

	virtual void OnNotify(const dae::GameObject& obj, Message message) override;

	void Render();
private:
	std::vector<std::shared_ptr<TextComponent>> m_TextComponents;

	static float m_Y;
	float m_X = 10.f;
};