#pragma once
#include <string>
#include <mutex>
#include <fstream>

class Logger {
private:
	std::mutex _mutex;
	std::ofstream _fs;
	Logger();
	Logger(const Logger&);
public:
	static Logger& GetInstance();
	void Log(std::string message);
	~Logger();
};
