#include <Recognizer.h>


Recognizer::Recognizer(): _width(320), _height(240){

}

void Recognizer::detect(cv::Mat& frame){
	HandDetector::getInstance()->detect(frame);
	GestureRecognizer::getInstance()->detect();
}


int Recognizer::getWidth(){
	return _width;
}

int Recognizer::getHeight(){
	return _height;
}

Recognizer::~Recognizer(){

}
