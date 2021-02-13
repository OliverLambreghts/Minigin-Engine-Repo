#include "MiniginPCH.h"
#include "FPSComponent.h"

FPSComponent::FPSComponent(TextComponent* comp, void (TextComponent::* fcnPtr) (std::string), GameObject& obj)
{
	m_Wrapper = std::bind(fcnPtr, comp, std::placeholders::_1);
	const std::function<void(float, GameObject&)> updateWrapper = std::bind(&FPSComponent::Update, this, std::placeholders::_1, std::placeholders::_2);
	obj.AddUpdateData(updateWrapper);
}

void FPSComponent::Update(float elapsedSec, GameObject&)
{
	int FPS = int(1 / elapsedSec);
	m_Wrapper(std::to_string(FPS) + " FPS");
}
