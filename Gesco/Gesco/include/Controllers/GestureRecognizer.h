/*
 * GestureRecognizer.h
 *
 *  Created on: 16/04/2013
 *      Author: cesar
 */

#ifndef GESTURERECOGNIZER_H_
#define GESTURERECOGNIZER_H_

#include <Kernel/Hand.h>
#include <Controllers/HandDetector.h>

// Confidence between two contours
#define  MAX_DIFFERENCE 0.2

// Percentage of the stdev that should be kept
#define CONTOUR_STDEV_DISPERSION 0.85 // The less, the more points remove



class GestureRecognizer{

	Hand* _hand;

	std::string _gesture;
	std::vector<std::vector<cv::Point> > _gesturesLib;

	// Debug
	DebugController* _debugController;

	// Get the bigest contour and removes the extreme points
	void processContours(std::vector<std::vector<cv::Point> >& contours, std::vector<cv::Point>& contour);

	void loadGesturesLib();

public:
	GestureRecognizer(Hand* hand);
	~GestureRecognizer();

	void detect();
	std::string& getRecognizedGesture();

	// Debug controller
	void setDebugController(DebugController* debugController);

};


#endif /* GESTURERECOGNIZER_H_ */
