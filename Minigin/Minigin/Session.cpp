#include "MiniginPCH.h"
#include "Session.h"

void Session::BeginSession(const std::string& filePath)
{
	m_OutputStream.open(filePath);
	m_OutputStream << "{\"traceEvents\":[";
	m_OutputStream.flush();
}

void Session::EndSession()
{
	m_OutputStream << "]}";
	m_OutputStream.flush();
	m_OutputStream.close();
	m_First = true;
}

void Session::SaveMeasurement(const std::string& name, int64_t start, int64_t end, const std::thread::id& id)
{
	if (m_First)
		m_First = false;
	else
		m_OutputStream << ",";

	m_OutputStream << "{" << "\"cat\":\"function\",\"dur\":" << (end - start) << ",\"name\":\"" << name << "\",";
	m_OutputStream << "\"ph\":\"X\",\"pid\":0," << "\"tid\":" << id << "," << "\"ts\":" << start << "}";

	m_OutputStream.flush();
}