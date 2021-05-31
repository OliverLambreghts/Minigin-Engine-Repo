#pragma once
#include "Observer.h"

class Subject final
{
public:
	void AddObserver(std::shared_ptr<Observer> observer);
	void RemoveObserver(std::shared_ptr<Observer> observer);

	void Notify(const dae::GameObject& obj, Message message);
private:
	std::vector<std::shared_ptr<Observer>> m_Observers;
};
