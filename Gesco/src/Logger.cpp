/*
 * Logger.cpp
 *
 *  Created on: 20/02/2011
 *      Author: cesar
 */

#include "Logger.h"

Logger::Logger() {
	_logFile.open("log", std::ios::trunc);

	if (_logFile.is_open()) {
		_logFile << "--Gesture Recognizer's log--" << std::endl;
	}
}

void Logger::out(std::string msg) {
	_logFile << ">" << msg << std::endl;
	std::cout << ">" << msg << std::endl;
}

void Logger::error(std::string msg) {
	_logFile << "[ERROR]" << msg << std::endl;
#ifdef WIN32
	std::cout<<"[ERROR] "<<msg<<std::endl;
#else
	std::cout << "[\x1b[31m\x1b[1m" <<"ERROR" << "\x1b[0m] "<<msg<< std::endl;
#endif
}

void Logger::warning(std::string msg) {
	_logFile << "[WARNING]" << msg << std::endl;
#ifdef WIN32
	std::cout<<"[WARNING] "<<msg<<std::endl;
#else
	std::cout << "[\x1b[33m\x1b[1m" <<"WARNING" << "\x1b[0m] "<<msg<< std::endl;
#endif
}

Logger::~Logger() {
}
