#pragma once
#include "GameObject.h"
#include "Scene.h"
#include "UIComponent.h"

class UIButton;
class UIElement;
class Command;
using namespace dae;
class UIWindowComponent final : public UIComponent
{
public:
	UIWindowComponent(Scene& scene, std::string name);
	virtual ~UIWindowComponent() = default;
	UIWindowComponent(const UIWindowComponent& other) = delete;
	UIWindowComponent(UIWindowComponent&& other) = delete;
	void operator=(const UIWindowComponent& rhs) = delete;
	void operator=(const UIWindowComponent&& rhs) = delete;

	void AddElement(std::shared_ptr<UIElement> element);
	template<typename T>
	void AddCommand(UINT id)
	{
		m_UICommands[id].second = std::make_shared<T>();
	}
	
	virtual void Update(float elapsedSec, GameObject& obj) override;

	virtual void Render() override;
	
	void AddActivationButton(std::shared_ptr<UIButton> button);

	bool IsActive(UINT id);
private:
	void RenderElements() const;
	
	std::string m_Name;
	std::vector<std::pair<std::shared_ptr<UIElement>, std::shared_ptr<Command>>> m_UICommands;

	std::shared_ptr<UIButton> m_pActivationButton = nullptr;
};