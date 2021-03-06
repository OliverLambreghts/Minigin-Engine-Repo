#pragma once
#include <chrono>
#include <string>

#define STR(s) #s
#define XSTR(s) STR(s)

#define MEASURE 1
#if MEASURE
#define TIME() Timer Time{__FUNCTION__ "-" XSTR(__LINE__)}
#else
#define TIME()
#endif

class Timer
{
public:
	Timer(const std::string& name);
	~Timer();
private:
	std::string m_Name;
	std::chrono::time_point<std::chrono::high_resolution_clock > m_StartTimePoint;
};