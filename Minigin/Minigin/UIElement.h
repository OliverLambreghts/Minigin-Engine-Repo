#pragma once

class UIElement
{
public:
	virtual ~UIElement() = default;
	virtual void Update() = 0;
	virtual void Render() = 0;

	virtual bool IsActive() = 0;
};