/*
 * HandDetector.h
 *
 *  Created on: 20/02/2011
 *      Author: cesar
 */

#ifndef HANDDETECTOR_H_
#define HANDDETECTOR_H_

#include <vector>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include <Kernel/Hand.h>
#include <Controllers/DebugController.h>

// BackProjection threshold
#define BACK_PROJ_THRES 5

// Get moving seedPoint
#define MIN_DIFF_MOV 50
#define MIN_DIFF_POINTS 400

// Initial thresholds => frameWithMask
#define EXT_MIN_S 60
#define EXT_MIN_V 60

// Look for the seedPoint around
#define SEED_POINT_KERNEL 25
#define SEED_POINT_LOCAL_KERNEL 20 // Big local kernel if big skin mask

// FloodFill parameter
#define FLOODFILL_PARAM 35

// Background mask
#define ACCUMULATOR_SPEED 0.1
#define THRES_ACCUMULATOR 100

// Difference Mask
#define THRES_DIFF_MASK 5

// Dilation
#define EROSION_ITERATIONS 3


class HandDetector{

	// Conversions of the original frame
	cv::Mat _frame;
	cv::Mat _frameBlur;
	cv::Mat _frameGray;
	cv::Mat _frameGrayBlur;
	cv::Mat _frameHSV;
	std::vector<cv::Mat> _vectorFrameHSV;

	// Previous frame
	cv::Mat _prevframe;

	// Difference frame
	cv::Mat _movFrame;

	// Background accumulator
	cv::Mat _backgroundAcc;

	// Skin histograms
	std::vector<cv::MatND> _skinHistograms;

	// Hand
	Hand* _hand;

	// Resizing width and height
	int _width, _height;

	// Debug
	DebugController* _debugController;

	void getSkinMask(std::vector<cv::Mat>& masks);
	void getFloodedMask(cv::Mat& frame, cv::Mat& gestureMask);
	void getBackgroundMask(cv::Mat& frame, cv::Mat& backgroundMask);

	bool interpolateSeedPoint(cv::Mat& skinMask, cv::Mat& frameWithMask);
	bool findMovingSeedPoint();

	void loadSkinHistograms();
	bool storeFrames(cv::Mat& frame);

public:
	HandDetector(Hand* hand, int width, int height);
	virtual ~HandDetector();

	void detect(cv::Mat& frame);

	// Debug controller
	void setDebugController(DebugController* debugController);
};

#endif /* DETECTIONCONTROLLER_H_ */
