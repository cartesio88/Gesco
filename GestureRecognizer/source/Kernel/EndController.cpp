/*
 * EndController.cpp
 *
 *  Created on: 20/05/2011
 *      Author: cesar
 */

#include <Kernel/EndController.h>

EndController::EndController(){
	_running = true;
}

bool EndController::isRunning(){
	return _running;
}

void EndController::end(){
	_running = false;
}

EndController::~EndController(){
}
