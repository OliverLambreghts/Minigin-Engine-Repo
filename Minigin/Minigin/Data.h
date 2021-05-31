#pragma once
#include "BaseData.h"
#include <functional>

// Class to handle data communication between components

template<typename returnType, typename getterType, typename setterType>
class Data final : public BaseData
{
public:
	void Link(getterType* getter, returnType(getterType::*getterFcn)(), setterType* setter, void(setterType::*setterFcn)(returnType))
	{
		m_Getter = std::bind(getterFcn, getter);
		m_Setter = std::bind(setterFcn, setter, std::placeholders::_1);
	}

	// This method will update data by calling saved setters with the getter's data as data injection
	virtual void Update() override
	{
		if (m_Data == m_Getter())
			return;
		m_Data = m_Getter();
		m_Setter(m_Data);
	}
private:
	std::function < returnType() > m_Getter;
	std::function< void(returnType) > m_Setter;
	returnType m_Data;
};
