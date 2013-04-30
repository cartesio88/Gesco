/*
 * World.cpp
 *
 *  Created on: 21/02/2011
 *      Author: cesar
 */

#include <Kernel/World.h>

using namespace cv;
using namespace std;

World::World():  _width(320), _height(240), _ticksLastEvent(0){
}

void World::initWorld(int width, int height) {
	Logger::getInstance()->out("Initializing world...");

	_width = width;
	_height = height;

	_noGestureRecognizedImg = Mat::zeros(Size(_width, _height), CV_8UC1);
	_gestureRecognizedImg = _noGestureRecognizedImg;

	SDL_Init(SDL_INIT_EVERYTHING);
	//SDL_SetVideoMode(width, height,24,0);

	// Original frame
	namedWindow("OriginalFrame", WINDOW_AUTOSIZE );
	cvMoveWindow("OriginalFrame", 0, 0);

	// Gesture recognized
	namedWindow("GestureRecognized", WINDOW_AUTOSIZE );
	cvMoveWindow("GestureRecognized", 0, _height+60);

	int x=_width +15;
	int y=0;

	for(int i=0; i < TEST_WINDOWS; i++){
		stringstream ss;
		ss<<"Test"<<i<<"Window";
		namedWindow(ss.str(), WINDOW_AUTOSIZE);
		cvMoveWindow(ss.str().c_str(), x, y);
		x += _width + 15;
		if(x > (1366 - _width)){
			x = _width + 15;
			y += _height + 60;
		}
	}

	_ticksLastEvent = SDL_GetTicks();

	for (int i = 0; i < TEST_WINDOWS; i++)
			_testFramesVector.push_back(Mat());

	Logger::getInstance()->out("World succesfully loaded!");
}

void World::drawWorld() {
	//Draw the camera frame
	Mat originalFrame;
	cv::Mat* frame = VideoFactory::getInstance()->getMainCamera().getLastFrame();
	resize(*frame, originalFrame,Size(_width,_height));

	imshow("OriginalFrame", originalFrame);

	for(unsigned int i=0; i<_testFramesVector.size(); i++){
		stringstream ss;
		ss<<"Test"<<i<<"Window";
		Mat& testFrame = _testFramesVector.at(i);
		if(testFrame.rows > 0) imshow(ss.str(), testFrame);
	}

	// Gesture recognized logic
	if(_timerShowGestureRecognized > 0){
		_timerShowGestureRecognized--;
	}else if(_timerShowGestureRecognized == 0){
		_timerShowGestureRecognized--;
		_gestureRecognizedImg = _noGestureRecognizedImg;
	}

	imshow("GestureRecognized", _gestureRecognizedImg);

	// Wait time
	Uint32 ticksNow = SDL_GetTicks();
	Uint32 ticksDiff = ticksNow - _ticksLastEvent;

	int waitTime = 1000/FPS - ticksDiff;

	if(waitTime > 0) {
		waitKey(waitTime);
	}

	_ticksLastEvent = ticksNow;
	waitKey(1);
}


void World::setTestFrame(unsigned int n, cv::Mat& mat){
	if(n<0 || n>= _testFramesVector.size()){
		cout<<"TestFrame number incorrect!"<<endl;
		return;
	}
	mat.copyTo(_testFramesVector.at(n));

}

void World::setGestureRecognized(cv::Mat& gestureImg){
	_timerShowGestureRecognized = SHOW_GESTURE_TIME;
	_gestureRecognizedImg = gestureImg;

}

int World::getWidth() {
	return _width;
}

int World::getHeight() {
	return _height;
}


World::~World() {
}
