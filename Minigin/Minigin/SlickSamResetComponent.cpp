#include "MiniginPCH.h"
#include "SlickSamResetComponent.h"
#include "GraphicsComponent2D.h"
#include "SlickSamTransformComponent.h"

void SlickSamResetComponent::Update(float, GameObject&)
{
	
}

void SlickSamResetComponent::Reset(std::shared_ptr<GameObject>& obj)
{
	obj->GetComponent<SlickSamTransformComponent>()->Reset();
	obj->GetComponent<GraphicsComponent2D>()->SetVisibility(false);
}