/*
 * Hand.h
 *
 *  Created on: 18/04/2013
 *      Author: cesar
 */

#ifndef HAND_H_
#define HAND_H_

#include <opencv2/opencv.hpp>


class Hand{

	cv::Point _seedPoint;
	// Blob
	// int gesture

	std::vector<cv::Mat> _handsMasks;

public:

	int getGesture();
	float* getMovementVector();

	std::vector<cv::Mat>& handsMasks(){return _handsMasks;}
	cv::Point& seedPoint(){ return _seedPoint;}
};



#endif /* HAND_H_ */
