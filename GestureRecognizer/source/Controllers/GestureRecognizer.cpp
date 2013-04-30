/*
 * GestureRecognizer.cpp
 *
 *  Created on: 16/04/2013
 *      Author: cesar
 */

#include <Controllers/GestureRecognizer.h>

using namespace std;
using namespace cv;

GestureRecognizer::GestureRecognizer() {
	_world = World::getInstance();
	loadGesturesLib();
}

void GestureRecognizer::detect() {
	vector<cv::Mat>& handFrames = HandDetector::getInstance()->getHandFrames();

	// Select the minimum
	double minDifference = 99;
	vector<Point> recognizedContour;
	vector<vector<Point> > contours;
	vector<Point> contour;
	vector<Point> recognizedGesture;

	for (unsigned int frameId = 0; frameId < handFrames.size(); frameId++) {
		findContours(handFrames.at(frameId), contours, CV_RETR_EXTERNAL,
				CV_CHAIN_APPROX_SIMPLE);

		processContours(contours, contour);

		for (unsigned int gestId = 0; gestId < _gesturesLib.size(); gestId++) {

			double difference;
			try {
				difference = matchShapes(contour, _gesturesLib.at(gestId),
						CV_CONTOURS_MATCH_I1, 0);
			} catch (cv::Exception& e) {
				continue;
			}

			if (difference < minDifference) {
				minDifference = difference;
				recognizedContour = contour;
				recognizedGesture = _gesturesLib.at(gestId);
			}
		}

	}

	if (minDifference < MAX_DIFFERENCE) {
		vector<vector<Point> > gesturesVector;
		gesturesVector.push_back(recognizedGesture);
		Mat gestureRecognizedImg = Mat::zeros(
				Size(_world->getWidth(), _world->getHeight()), CV_8UC3);
		drawContours(gestureRecognizedImg, gesturesVector, -1, Scalar(0, 0, 250),
				2);
		_world->setGestureRecognized(gestureRecognizedImg);

		//Rep
		vector<vector<Point> > contoursVector;
		contoursVector.push_back(recognizedContour);
		Mat contourImg = Mat::zeros(Size(_world->getWidth(), _world->getHeight()), CV_8UC1);
		drawContours(contourImg, contoursVector, -1, Scalar(255), 2);
		_world->setTestFrame(5, contourImg);

	}
}

// Deletes the points that are "far away from the seed point",
//  and selects the biggest contour

void GestureRecognizer::processContours(
		std::vector<std::vector<cv::Point> >& contours,
		std::vector<cv::Point>& contour) {
	vector<float> distances;
	double stdev = 0;

	// Select the biggest contour
	size_t maxPoints = 0;
	vector<cv::Point>& selectedContour = contour;
	vector<vector<Point> >::iterator itContour;
	for (itContour = contours.begin(); itContour != contours.end();
			++itContour) {
		if ((*itContour).size() > maxPoints) {
			maxPoints = (*itContour).size();
			selectedContour = (*itContour);
		}
	}

	Point& seedPoint = HandDetector::getInstance()->getSeedPoint();

	//Calculate and stdev, and keep the max dist
	float maxDist = 0;
	vector<Point>::iterator itPoint;
	for (itPoint = selectedContour.begin(); itPoint != selectedContour.end();
			++itPoint) {
		Point& p = *itPoint;
		float dist = sqrt(
				pow((float) (p.x - seedPoint.x), 2)
						+ pow((float) (p.y - seedPoint.y), 2));
		if (dist > maxDist)
			maxDist = dist;
		stdev += dist;
		distances.push_back(dist);
	}
	stdev = stdev / selectedContour.size();

	// Delete those points that are farther than 90% of stdev
	vector<Point> newContour;
	if ((stdev / maxDist) < CONTOUR_STDEV_DISPERSION) {
		float threshold = CONTOUR_STDEV_DISPERSION * maxDist;
		for (unsigned int i = 0; i < distances.size(); ++i) {
			float& dist = distances.at(i);
			if (dist < threshold) {
				newContour.push_back(selectedContour.at(i));
			}
		}
	}

	contour = newContour;
}

void GestureRecognizer::loadGesturesLib() {
	int gestN = 1;
	cout << "Loading gestures library... " << flush;
	while (true) {
		vector<Point> gesture;
		stringstream ss;
		ss << "data/gestures/gesture" << gestN << ".yml";
		cv::FileStorage fs(ss.str(), cv::FileStorage::READ);
		if (!fs.isOpened()) {
			break;
		} else {
			fs["gesture"] >> gesture;
			_gesturesLib.push_back(gesture);
			gestN++;
			fs.release();
		}
	}
	cout << "Read " << (gestN - 1) << " gestures!" << endl;
}

std::string& GestureRecognizer::getRecognizedGesture() {
	return _gesture;
}

GestureRecognizer::~GestureRecognizer() {

}

