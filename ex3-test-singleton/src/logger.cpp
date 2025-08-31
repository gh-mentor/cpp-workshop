
#include "logger.h"
#include <iostream>
#include <cassert>
#include <fstream>
#include <mutex>

std::string fileName = "log.txt";

Logger::Logger() {
	_fs.open(fileName, std::ios_base::app);
}

Logger& Logger::GetInstance() {
	static Logger _logger;
	return _logger;
}

void Logger::Log(std::string message) {
	std::lock_guard<std::mutex> lg(_mutex);
	_fs << message << std::endl;
}

Logger::~Logger() {
	_fs.close();
}

