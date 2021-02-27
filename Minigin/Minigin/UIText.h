#pragma once
#include "UIElement.h"
#include <string>

class UIText : public UIElement
{
public:
	UIText(std::string text);

	virtual ~UIText() = default;

	virtual void Update() override;

	virtual void Render() override;

	void SetText(std::string text);

	virtual bool IsActive() override;
private:
	std::string m_Text;
};