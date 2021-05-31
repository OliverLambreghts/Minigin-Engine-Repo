#pragma once
#include "Observer.h"

class Resetter final : public Observer
{
public:
	Resetter() = default;

	virtual ~Resetter() = default;
	Resetter(const Resetter& other) = delete;
	Resetter(Resetter&& other) = delete;
	void operator=(const Resetter& rhs) = delete;
	void operator=(const Resetter&& rhs) = delete;

	void AddData(std::function<void()>& resetFcn);

	virtual void OnNotify(const dae::GameObject& obj, Message message) override;
private:
	std::function<void()> m_pResetFcn;
};
