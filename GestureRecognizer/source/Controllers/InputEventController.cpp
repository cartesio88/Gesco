/*
 * InputEventController.cpp
 *
 *  Created on: 20/02/2011
 *      Author: cesar
 */

#include <Controllers/InputEventController.h>

InputEventController::InputEventController() {

}

void InputEventController::pollEvents() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		//Mouse events
		case SDL_MOUSEMOTION:
			break;
		case SDL_MOUSEBUTTONDOWN:
			break;
		case SDL_MOUSEBUTTONUP:
			break;
			//Keyboard events
		case SDL_KEYDOWN:
			std::cout<<"Tecla pulsada"<<std::endl;
			if(event.key.keysym.sym==SDLK_ESCAPE) EndController::getInstance()->end();
			break;
		case SDL_KEYUP:
			break;
			//Quit event
		case SDL_QUIT:
			EndController::getInstance()->end();
			break;
		}
	}
}


InputEventController::~InputEventController() {
}
