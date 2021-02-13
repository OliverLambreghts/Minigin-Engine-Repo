#pragma once
#include <functional>
#include "CalculationComponent.h"
#include "TextComponent.h"

using namespace dae;
class FPSComponent : public CalculationComponent
{
public:
	FPSComponent(TextComponent* comp, void (TextComponent::* fcnPtr) (std::string), GameObject& obj);
	virtual ~FPSComponent() = default;
	FPSComponent(const FPSComponent& other) = delete;
	FPSComponent(FPSComponent&& other) = delete;
	void operator=(const FPSComponent& rhs) = delete;
	void operator=(const FPSComponent&& rhs) = delete;

	virtual void Update(float elapsedSec, GameObject& obj) override;
private:
	std::function<void(std::string)> m_Wrapper;
};