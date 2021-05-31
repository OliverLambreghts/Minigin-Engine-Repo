#pragma once
#include "UIElement.h"

class UIButton final : public UIElement
{
public:
	UIButton(std::string name, bool staysActive);
	
	virtual ~UIButton() = default;
	UIButton(const UIButton& other) = delete;
	UIButton(UIButton&& other) = delete;
	void operator=(const UIButton& rhs) = delete;
	void operator=(const UIButton&& rhs) = delete;
	
	virtual void Update() override;

	virtual void Render() override;

	void SetName(std::string name);
	
	virtual bool IsActive() override;
private:
	std::string m_Name;
	bool m_IsActive = false, m_StaysActive;
};