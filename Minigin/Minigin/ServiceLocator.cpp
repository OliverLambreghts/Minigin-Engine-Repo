#include "MiniginPCH.h"
#include "ServiceLocator.h"

NullAudioService ServiceLocator::m_NullService{};
AudioService* ServiceLocator::m_pASInstance = &m_NullService;

AudioService* ServiceLocator::GetAudioService()
{
	return m_pASInstance;
}

void ServiceLocator::Provide(AudioService* service)
{
	if (!service) m_pASInstance = &m_NullService;
	else m_pASInstance = service;
}

void ServiceLocator::Destroy()
{
	delete m_pASInstance;
	m_pASInstance = nullptr;
}