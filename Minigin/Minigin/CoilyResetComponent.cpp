#include "MiniginPCH.h"
#include "CoilyResetComponent.h"

#include "CoilyTransformComponent.h"
#include "GraphicsComponent2D.h"

void CoilyResetComponent::Update(float , GameObject& )
{
}

void CoilyResetComponent::Reset(std::shared_ptr<GameObject>& ptr)
{
	ptr->GetComponent<CoilyTransformComponent>()->Reset();
	ptr->GetComponent<GraphicsComponent2D>()->ChangeTexture("../Data/QBert/Enemies/Coily/Egg.png");
	ptr->GetComponent<GraphicsComponent2D>()->SetVisibility(false);
}