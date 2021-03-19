#pragma once
#include "NullAudioService.h"

class AudioService;

class ServiceLocator final
{
public:
	static AudioService* GetAudioService();
	static void Provide(AudioService* service);

	static void Destroy();
private:
	static AudioService* m_pASInstance;
	static NullAudioService m_NullService;
};
