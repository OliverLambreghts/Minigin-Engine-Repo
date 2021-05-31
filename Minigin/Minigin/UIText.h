#pragma once
#include "UIElement.h"
#include <string>

class UIText final : public UIElement
{
public:
	UIText(std::string text);

	virtual ~UIText() = default;
	UIText(const UIText& other) = delete;
	UIText(UIText&& other) = delete;
	void operator=(const UIText& rhs) = delete;
	void operator=(const UIText&& rhs) = delete;

	virtual void Update() override;

	virtual void Render() override;

	void SetText(std::string text);

	virtual bool IsActive() override;
private:
	std::string m_Text;
};