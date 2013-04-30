/*
 * EndController.h
 *
 *  Created on: 20/05/2011
 *      Author: cesar
 */

#ifndef ENDCONTROLLER_H_
#define ENDCONTROLLER_H_

#include <Kernel/Singleton.h>

class EndController: public Singleton<EndController>{
public:
	EndController();
	virtual ~EndController();
	bool isRunning();
	void end();
private:
	bool _running;

};

#endif
