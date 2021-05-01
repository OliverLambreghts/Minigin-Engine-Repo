#include "MiniginPCH.h"
#include "CoilyResetComponent.h"

#include "CoilyTransformComponent.h"
#include "GraphicsComponent2D.h"

void CoilyResetComponent::Update(float , GameObject& )
{
}

void CoilyResetComponent::Reset(std::shared_ptr<GameObject>& obj)
{
	obj->GetComponent<CoilyTransformComponent>()->Reset();
	obj->GetComponent<GraphicsComponent2D>()->ChangeTexture("../Data/QBert/Enemies/Coily/Egg.png");
	obj->GetComponent<GraphicsComponent2D>()->SetVisibility(false);
}