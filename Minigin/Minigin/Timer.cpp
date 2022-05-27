#include "MiniginPCH.h"
#include "Timer.h"
#include "Session.h"

Timer::Timer(const std::string& name)
	: m_Name{name},
	m_StartTimePoint({ std::chrono::high_resolution_clock::now() })
{
}

Timer::~Timer()
{
	const auto endTimePoint = std::chrono::high_resolution_clock::now();
	const int64_t begin = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch().count();
	const int64_t end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

	Session::GetInstance().SaveMeasurement(m_Name, begin, end, std::this_thread::get_id());
	//std::cout << "[" << m_Name << "] " << end - begin << " microseconds\n";
}