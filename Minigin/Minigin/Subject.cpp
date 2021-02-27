#include "MiniginPCH.h"
#include "Subject.h"

void Subject::AddObserver(std::shared_ptr<Observer> observer)
{
	m_Observers.push_back(observer);
}

void Subject::RemoveObserver(std::shared_ptr<Observer> observer)
{
	m_Observers.erase(std::remove(m_Observers.begin(), m_Observers.end(), observer), 
		m_Observers.end());
}

void Subject::Notify(const dae::GameObject& obj, Message message)
{
	for (const auto& observer : m_Observers)
	{
		observer->OnNotify(obj, message);
	}
}