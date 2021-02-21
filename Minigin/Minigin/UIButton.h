#pragma once
#include "UIElement.h"

class UIButton : public UIElement
{
public:
	UIButton(std::string name);
	
	virtual ~UIButton() = default;
	
	virtual void Update() override;

	virtual void Render() override;

	void SetName(std::string name);
	
	virtual bool IsActive() override;
private:
	std::string m_Name;
	bool m_IsActive = false;
};