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
#include <Kernel/World.h>
#include <Kernel/Singleton.h>

// BackProjection threshold
#define BACK_PROJ_THRES 5

// Get moving seedPoint
#define MIN_DIFF_MOV 50
#define MIN_DIFF_POINTS 400

// Initial threshols => frameWithMask
//#define EXT_MAX_S 255
#define EXT_MIN_S 60
#define EXT_MIN_V 60

// Look for the seedPoint around
#define SEED_POINT_KERNEL 25
#define SEED_POINT_LOCAL_KERNEL 20 // Big local kernel if big sking mask

// FloodFill parameter
#define FLOODFILL_PARAM 35

// Background mask
#define ACCUMULATOR_SPEED 2.f * 1/FPS
#define ACCUMULATOR_SPEED_FAST 9999999999999.f * 1/FPS
#define THRES_ACCUMULATOR 100

// Difference Mask
#define THRES_DIFF_MASK 5

// Dilation
#define EROSION_ITERATIONS 3

class HandDetector: public Singleton<HandDetector>{
	World* _world;

	cv::Mat _prevOriginalFrame;
	cv::Mat _differenceFrame;

	cv::Mat _originalFrame;
	cv::Mat _originalFrameBlur;
	cv::Mat _originalFrameGray;
	cv::Mat _originalFrameGrayBlur;
	cv::Mat _originalFrameHSV;
	std::vector<cv::Mat> _vectorOriginalFrameHSV;

	cv::Mat _backgroundAccumulator;

	std::vector<cv::Mat> _handFrames;
	std::vector<cv::MatND> _skinHistograms;

	cv::Point _seedPoint;

	// Debug
	int _itSeedPoint;

	void getSkinMask(std::vector<cv::Mat>& masks);
	void getFloodedMask(cv::Mat& frame, cv::Mat& gestureMask);
	void getBackgroundMask(cv::Mat& frame, cv::Mat& backgroundMask, cv::Mat& mask);

	bool interpolateSeedPoint(cv::Mat& skinMask, cv::Mat& frameWithMask);
	bool findMovingSeedPoint();

	void loadSkinHistograms();
	bool storeFrames();

public:
	HandDetector();
	virtual ~HandDetector();

	void detect();

	cv::Mat& getOriginalFrame();
	std::vector<cv::Mat>& getHandFrames();
	cv::Point& getSeedPoint();

};

#endif /* DETECTIONCONTROLLER_H_ */
