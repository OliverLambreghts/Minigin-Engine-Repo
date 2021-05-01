#pragma once
#include "Observer.h"

class Resetter : public Observer
{
public:
	Resetter() = default;

	void AddData(std::function<void()>& resetFcn);

	virtual void OnNotify(const dae::GameObject& obj, Message message) override;
private:
	std::function<void()> m_pResetFcn;
};
