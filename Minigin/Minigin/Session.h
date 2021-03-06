#pragma once
#include <fstream>
#include <thread>

#include "Singleton.h"

class Session : public dae::Singleton<Session>
{
public:
	void BeginSession(const std::string& filePath = "measurements.json");
	void EndSession();
	void SaveMeasurement(const std::string& name, int64_t start, int64_t end, const std::thread::id& id);
private:
	friend class Singleton<Session>;
	std::ofstream m_OutputStream;
	bool m_First;
	Session() : m_First{ true } {}
};
