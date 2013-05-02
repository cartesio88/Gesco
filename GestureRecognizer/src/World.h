/*
 * World.h
 *
 *  Created on: 21/02/2011
 *      Author: cesar
 */

#ifndef WORLD_H_
#define WORLD_H_

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <SDL.h>

#include "VideoFactory.h"
#include "Logger.h"
#include "Singleton.h"

#define FPS 15
#define TEST_WINDOWS 6

#define SHOW_GESTURE_TIME 1.5*FPS;

class World: public Singleton<World> {
	int _width;
	int _height;
	Uint32 _ticksLastEvent;
	cv::Mat _gestureRecognizedImg;
	cv::Mat _noGestureRecognizedImg;
	int _timerShowGestureRecognized;
	std::vector<cv::Mat> _testFramesVector;

public:
	World();
	virtual ~World();
	void initWorld(int width, int height);
	void drawWorld();

	int getWidth();
	int getHeight();
	void setTestFrame(unsigned int n, cv::Mat& mat);

	void setGestureRecognized(cv::Mat& gestureImg);


};


#endif /* WORLD_H_ */
