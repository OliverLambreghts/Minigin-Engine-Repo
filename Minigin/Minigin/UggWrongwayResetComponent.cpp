#include "MiniginPCH.h"
#include "UggWrongWayResetComponent.h"
#include "UggWrongwayTransformComponent.h"
#include "GraphicsComponent2D.h"

void UggWrongwayResetComponent::Update(float , GameObject& )
{
	
}

void UggWrongwayResetComponent::Reset(std::shared_ptr<GameObject>& obj)
{
	obj->GetComponent<UggWrongWayTransformComponent>()->Reset();
	obj->GetComponent<GraphicsComponent2D>()->SetVisibility(false);
}