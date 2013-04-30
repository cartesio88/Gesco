/*
 * Logger.h
 *
 *  Created on: 20/02/2011
 *      Author: cesar
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <Kernel/Singleton.h>
#include <string>
#include <fstream>

class Logger : public Singleton<Logger>{
public:
	Logger();
	virtual ~Logger();
	void out(std::string msg);
	void error(std::string msg);
	void warning(std::string msg);

private:
	std::ofstream _logFile;

};

#endif /* LOGGER_H_ */
