/*
 * InputEventController.h
 *
 *  Created on: 20/02/2011
 *      Author: cesar
 */

#ifndef INPUTEVENTCONTROLLER_H_
#define INPUTEVENTCONTROLLER_H_

#include <vector>
#include <SDL.h>
#include <Kernel/Singleton.h>
#include <Kernel/Logger.h>
#include <Kernel/EndController.h>

class InputEventController: public Singleton<InputEventController> {
public:
	InputEventController();
	virtual ~InputEventController();

	void pollEvents();

private:

};

#endif /* INPUTEVENTCONTROLLER_H_ */
