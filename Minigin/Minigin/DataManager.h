#pragma once
#include "Data.h"
#include <vector>
#include <memory>

class DataManager final
{
public:
	template<typename returnType, typename getterType, typename setterType>
	void LinkData(getterType* getter, returnType(getterType::* getterFcn)(), setterType* setter, void(setterType::* setterFcn)(returnType))
	{
		auto data = std::make_shared<Data<returnType, getterType, setterType>>();
		data->Link(getter, getterFcn, setter, setterFcn);
		m_Data.push_back(data);
	}

	void Update();
private:
	std::vector<std::shared_ptr<BaseData>> m_Data;
};