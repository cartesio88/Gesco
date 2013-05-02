/*
 * HandDetector.cpp
 *
 *  Created on: 20/02/2011
 *      Author: cesar
 */

#include <Controllers/HandDetector.h>

using namespace cv;
using namespace std;

HandDetector::HandDetector() :
		_itSeedPoint(0) {

	_seedPoint = Point(Recognizer::getInstance()->getHeight() / 2,
			Recognizer::getInstance()->getWidth() / 2);

	loadSkinHistograms();

}

void HandDetector::detect(cv::Mat& frame) {

	// Grab the frame
	if (!storeFrames(frame))
		return;

	// Get difference mask
	Mat differenceMask;
	threshold(_differenceFrame, differenceMask, THRES_DIFF_MASK, 255,
			THRESH_BINARY);

	// Get skin mask
	vector<Mat> skinMasks(_skinHistograms.size());
	getSkinMask(skinMasks);

	// Clear them
	_handFrames.clear();

	// For each histogram
	for (unsigned int i = 0; i < _skinHistograms.size(); i++) {

		Mat diffSkinMask = differenceMask | skinMasks.at(i);

		// Get background mask
		Mat backgroundMask;
		getBackgroundMask(_originalFrameBlur, backgroundMask, diffSkinMask);

		Mat back2;
		back2 = backgroundMask & diffSkinMask;

		Mat back3;
		erode(back2, back3, Mat());

		// Find seed! Movement + skin mask :)
		findMovingSeedPoint();
		if (!skinMasks.at(i).at<uchar>(_seedPoint.y, _seedPoint.x)
				&& !interpolateSeedPoint(skinMasks.at(i), _originalFrame)) {
			return;
		}

		Mat floodedFrame;
		getFloodedMask(back3, floodedFrame);

		// Draw the seed point
		// Rep
		circle(floodedFrame, _seedPoint, 3, Scalar(80), 5);

		_handFrames.push_back(floodedFrame);

	}
}

void HandDetector::getSkinMask(std::vector<cv::Mat>& masks) {

	float h_range[] = { 0, 180 };
	float s_range[] = { 0, 255 };
	const float* ranges[] = { h_range, s_range };
	int channels[] = { 0, 1 };

	// Get Backprojection
	MatND backProj;
	for (unsigned int i = 0; i < _skinHistograms.size(); i++) {

		calcBackProject(&_originalFrameHSV, 1, channels, _skinHistograms.at(i),
				backProj, ranges, 1, true);

		threshold(backProj, masks.at(i), BACK_PROJ_THRES, 255, THRESH_BINARY);
	}

	return;
}

// Use accumulator!
void HandDetector::getBackgroundMask(cv::Mat& frame, cv::Mat& backgroundMask,
		cv::Mat& mask) {

	// Dont do that where the man moves!
	Mat maskInv;
	threshold(mask, maskInv, 180, 255, THRESH_BINARY_INV);

	accumulateWeighted(frame, _backgroundAccumulator, ACCUMULATOR_SPEED,
			maskInv);

	Mat backgroundImage;
	convertScaleAbs(_backgroundAccumulator, backgroundImage);

	// Difference frame
	backgroundMask = Mat::zeros(frame.rows, frame.cols, CV_8UC1);

	for (int i = 0; i < frame.rows; i++) {
		for (int j = 0; j < frame.cols; j++) {
			float diff = pow(
					(float) frame.at<uchar>(i, j * 3)
							- backgroundImage.at<uchar>(i, j * 3), 2)
					+ pow(
							(float) frame.at<uchar>(i, j * 3 + 1)
									- backgroundImage.at<uchar>(i, j * 3 + 1),
							2)
					+ pow(
							(float) frame.at<uchar>(i, j * 3 + 2)
									- backgroundImage.at<uchar>(i, j * 3 + 2),
							2);

			backgroundMask.at<uchar>(i, j) =
					(diff > THRES_ACCUMULATOR) ? 255 : 0;
		}
	}
}

void HandDetector::getFloodedMask(cv::Mat& frame, cv::Mat& floodedMask) {
	int newMaskVal = 255;
	int lo = FLOODFILL_PARAM;
	int up = FLOODFILL_PARAM;
	int connectivity = 4;
	int flags = connectivity + (newMaskVal << 8) + FLOODFILL_FIXED_RANGE
			+ FLOODFILL_MASK_ONLY;

	try {
		Mat mask;
		mask = Mat::zeros(frame.rows + 2, frame.cols + 2, CV_8UC1);

		floodFill(frame, mask, _seedPoint, Scalar(), 0, Scalar(lo, lo, lo),
				Scalar(up, up, up), flags);

		floodedMask = Mat(frame.rows, frame.cols, CV_8UC1);

		for (int i = 0; i < floodedMask.rows; i++) {
			for (int j = 0; j < floodedMask.cols; j++) {
				floodedMask.at<uchar>(i, j) = mask.at<uchar>(i + 1, j + 1);
			}
		}

	} catch (cv::Exception& e) {
		cout << "Error in floodFill: " << _seedPoint << endl;
	}
}

bool HandDetector::interpolateSeedPoint(cv::Mat& skinMask,
		cv::Mat& frameWithMask) {

	// Inside a KERNEL, look for a "bunch of white pixels", defined by LOCAL_KERNEL
	for (int i = _seedPoint.x - SEED_POINT_KERNEL;
			i < _seedPoint.x + SEED_POINT_KERNEL;
			i = i + SEED_POINT_LOCAL_KERNEL) {
		for (int j = _seedPoint.y - SEED_POINT_KERNEL;
				j < _seedPoint.y + SEED_POINT_KERNEL;
				j = j + SEED_POINT_LOCAL_KERNEL) {

			if (frameWithMask.at<Point3i>(i, j).x == 0)
				continue;

			if (i > SEED_POINT_LOCAL_KERNEL && j > SEED_POINT_LOCAL_KERNEL
					&& i < skinMask.cols - SEED_POINT_LOCAL_KERNEL
					&& j < skinMask.rows - SEED_POINT_LOCAL_KERNEL) {
				if (skinMask.at<uchar>(j, i)
						&& skinMask.at<uchar>(j - SEED_POINT_LOCAL_KERNEL, i)
						&& skinMask.at<uchar>(j + SEED_POINT_LOCAL_KERNEL, i)
						&& skinMask.at<uchar>(j, i - SEED_POINT_LOCAL_KERNEL)
						&& skinMask.at<uchar>(j, i + SEED_POINT_LOCAL_KERNEL)) {
					// Check sizes
					if (_seedPoint.x < 0 || _seedPoint.y < 0
							|| _seedPoint.x >= _originalFrame.cols
							|| _seedPoint.y >= _originalFrame.rows) {
						return false;
					}
					_seedPoint.x = i;
					_seedPoint.y = j;
					return true;
				}
			}
		}
	}

	return false;

}

bool HandDetector::findMovingSeedPoint() {

	int nPoints = 0;
	Point candidate(0, 0);

	for (int i = 0; i < _differenceFrame.cols; i++) {
		for (int j = 0; j < _differenceFrame.rows; j++) {
			if (_differenceFrame.at<uchar>(j, i) > MIN_DIFF_MOV) {
				nPoints++;
				candidate += Point(i, j);
			}
		}
	}

	if (nPoints > MIN_DIFF_POINTS) {
		candidate.x /= nPoints;
		candidate.y /= nPoints;

		_seedPoint = candidate;
		return true;
	}

	return false;
}

bool HandDetector::storeFrames(cv::Mat& frame) {

	if (_originalFrame.rows != 0) {
		// Saving to previous frame. In GRAY to save time
		cvtColor(_originalFrame, _prevOriginalFrame, CV_BGR2GRAY);

		//Mat preEqual;
		resize(frame, _originalFrame,
				Size(Recognizer::getInstance()->getWidth(),
						Recognizer::getInstance()->getHeight()));
		//equalizeHist(preEqual, _originalFrame);

		// Convert it to gray
		cvtColor(_originalFrame, _originalFrameGray, CV_BGR2GRAY);

		// Difference frame
		absdiff(_originalFrameGray, _prevOriginalFrame, _differenceFrame);

		// Gaussian Blur
		Mat auxsrc;
		Size GAUS_KERNEL(9, 9);
		double GAUS_SIGMA = 5;

		// Color blur
		GaussianBlur(_originalFrame, _originalFrameBlur, GAUS_KERNEL,
				GAUS_SIGMA);

		// Gray blur
		GaussianBlur(_originalFrameGray, _originalFrameGrayBlur, GAUS_KERNEL,
				GAUS_SIGMA);

		// Convert to HSV
		cvtColor(_originalFrameBlur, _originalFrameHSV, CV_BGR2HSV);
		split(_originalFrameHSV, _vectorOriginalFrameHSV);

		return true;
	} else {
		// Initializations here :)
		_backgroundAccumulator = Mat::zeros(
				Recognizer::getInstance()->getHeight(),
				Recognizer::getInstance()->getWidth(), CV_64FC3);

		resize(frame, _originalFrame,
				Size(Recognizer::getInstance()->getWidth(),
						Recognizer::getInstance()->getHeight()));

		// Gaussian Blur
		Mat auxsrc;
		Size GAUS_KERNEL(9, 9);
		double GAUS_SIGMA = 5;

		// Color blur
		GaussianBlur(_originalFrame, _originalFrameBlur, GAUS_KERNEL,
				GAUS_SIGMA);

		// Initialize the accumulator with the first frame TODO
		for (int i = 0; i < 2000; i++)
			accumulateWeighted(_originalFrameBlur, _backgroundAccumulator,
					ACCUMULATOR_SPEED);

		return false;
	}

}

void HandDetector::loadSkinHistograms() {
	int histN = 1;
	cout << "Loading skin histograms... " << flush;
	while (true) {
		cv::Mat histogram;
		stringstream ss;

		ss << "data/histograms/histogram" << histN << ".yml";
		cv::FileStorage fs(ss.str(), cv::FileStorage::READ);
		if (!fs.isOpened()) {
			break;
		} else {
			fs["histogram"] >> histogram;
			_skinHistograms.push_back(histogram);
			histN++;
			fs.release();
		}
	}
	cout << "Read " << (histN - 1) << " skin histogramms!" << endl;
}

cv::Point& HandDetector::getSeedPoint() {
	return _seedPoint;
}

Mat& HandDetector::getOriginalFrame() {
	return _originalFrame;
}

std::vector<cv::Mat>& HandDetector::getHandFrames() {
	return _handFrames;
}

HandDetector::~HandDetector() {
}
