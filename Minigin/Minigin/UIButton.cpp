#include "MiniginPCH.h"
#include "UIButton.h"
#include "imgui.h"

UIButton::UIButton(std::string name)
	: m_Name{name}
{
	
}

void UIButton::Update()
{
	
}

void UIButton::Render()
{
	if (ImGui::Button(m_Name.c_str()))
		m_IsActive = !m_IsActive;
}

void UIButton::SetName(std::string name)
{
	m_Name = name;
}

bool UIButton::IsActive()
{
	return m_IsActive;
}