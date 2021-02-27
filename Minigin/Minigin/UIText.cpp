#include "MiniginPCH.h"
#include "UIText.h"
#include "imgui.h"

UIText::UIText(std::string text)
	: m_Text{text}
{
	
}

void UIText::Update()
{
	
}

void UIText::Render()
{
	ImGui::Text(m_Text.c_str());
}

void UIText::SetText(std::string text)
{
	m_Text = text;
}

bool UIText::IsActive()
{
	return false;
}