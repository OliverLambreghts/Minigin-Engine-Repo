#include "MiniginPCH.h"
#include "Resetter.h"

void Resetter::AddData(std::function<void()>& resetFcn)
{
	m_pResetFcn = resetFcn;
}

void Resetter::OnNotify(const dae::GameObject& , Message message)
{
	switch(message)
	{
	case Message::PlayerDied:
		m_pResetFcn();
		break;
	}
}