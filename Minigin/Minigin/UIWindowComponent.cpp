#include "MiniginPCH.h"
#include "UIWindowComponent.h"
#include "imgui.h"
#include "UIButton.h"
#include "Command.h"

UIWindowComponent::UIWindowComponent(Scene& scene, std::string name)
	: m_Name{name}
{
	std::function<void()> renderWrapper = std::bind(&UIWindowComponent::Render, this);
	scene.AddRenderData(renderWrapper);
}

void UIWindowComponent::AddElement(std::shared_ptr<UIElement> element)
{
	m_UICommands.push_back(std::make_pair(element, nullptr));
}

void UIWindowComponent::AddActivationButton(std::shared_ptr<UIButton> button)
{
	m_pActivationButton = button;
}

void UIWindowComponent::Update(float, GameObject&)
{
	for(UINT i{}; i < m_UICommands.size(); ++i)
	{
		if(IsActive(i) && m_UICommands[i].second)
		{
			m_UICommands[i].second->Execute();
		}
	}
}

void UIWindowComponent::Render()
{
	if ((m_pActivationButton && m_pActivationButton->IsActive()) || !m_pActivationButton)
	{
		ImGui::Begin(m_Name.c_str());
		RenderElements();
		ImGui::End();
	}
}

void UIWindowComponent::RenderElements()
{
	for(const auto& element : m_UICommands)
	{
		element.first->Render();
	}
}

bool UIWindowComponent::IsActive(UINT id)
{
	return m_UICommands[id].first->IsActive();
}