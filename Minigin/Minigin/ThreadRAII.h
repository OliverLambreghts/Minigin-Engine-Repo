#pragma once
#include <thread>

class ThreadRAII
{
public:
	ThreadRAII(std::thread& thread);
	
	~ThreadRAII();
private:
	std::thread m_Thread;
};