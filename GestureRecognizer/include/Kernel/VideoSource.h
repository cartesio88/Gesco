/*
 * VideoSource.h
 *
 *  Created on: 20/02/2011
 *      Author: cesar
 */

#ifndef VIDEOSOURCE_H_
#define VIDEOSOURCE_H_

#include <opencv2/highgui/highgui.hpp>
#include <Kernel/Logger.h>
#include <string>


class VideoSource {
public:
	VideoSource(const std::string& name, const int& nDevice, int width = 640, int height = 480);
	virtual ~VideoSource();
	cv::Mat* grabFrame();
	cv::Mat* getLastFrame();
	std::string& getName();
	int getWidth();
	int getHeight();
	int getFps();

private:
	cv::Mat* _lastFrame;
	std::string _name;
	cv::VideoCapture* _cam;
	int _width;
	int _height;
	int _fps;
};

#endif /* VIDEOSOURCE_H_ */
