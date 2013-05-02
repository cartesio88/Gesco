/*
 * Recognizer.h
 *
 *  Created on: 01/05/2013
 *      Author: cesar
 */

#ifndef RECOGNIZER_H_
#define RECOGNIZER_H_

#include <Controllers/HandDetector.h>
#include <Controllers/GestureRecognizer.h>
#include <Kernel/Hand.h>

class Recognizer: public Singleton<Recognizer>{
	Hand hand;

	int _width, _height;

public:
	Recognizer();
	~Recognizer();

	void detect(cv::Mat& frame);
	int getWidth();
	int getHeight();
	// Debug interface :)



};

#endif /* RECOGNIZER_H_ */
