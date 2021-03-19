#include "MiniginPCH.h"
#include "ThreadRAII.h"

ThreadRAII::ThreadRAII(std::thread& thread)
	: m_Thread{std::move(thread)}
{
	
}

ThreadRAII::~ThreadRAII()
{
	if (m_Thread.joinable())
		m_Thread.join();
}