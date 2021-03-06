#pragma once
#include <functional>
#include "CalculationComponent.h"
#include "TextComponent.h"

using namespace dae;
class FPSComponent : public CalculationComponent
{
public:
	FPSComponent();
	virtual ~FPSComponent() = default;
	FPSComponent(const FPSComponent& other) = delete;
	FPSComponent(FPSComponent&& other) = delete;
	void operator=(const FPSComponent& rhs) = delete;
	void operator=(const FPSComponent&& rhs) = delete;

	virtual void Update(float elapsedSec, GameObject& obj) override;

	std::string GetFPS();
private:
	float m_Delay;
	float m_ResetPoint = 1.f;
	int m_FPS;
};