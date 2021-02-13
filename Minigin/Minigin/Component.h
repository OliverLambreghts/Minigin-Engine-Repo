#pragma once
#include "GameObject.h"

using namespace dae;
class Component
{
public:
	Component() = default;
	virtual ~Component() = default;
	Component(const Component& other) = delete;
	Component(Component&& other) = delete;
	void operator=(const Component& rhs) = delete;
	void operator=(const Component&& rhs) = delete;
};