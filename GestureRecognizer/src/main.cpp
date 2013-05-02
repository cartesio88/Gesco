/*
 * main.cpp
 *
 *  Created on: 19/02/2011
 *      Author: cesar
 *
 *      Test application
 */
#include "InputEventController.h"
#include "VideoFactory.h"
#include "VideoSource.h"
#include "EndController.h"
#include "World.h"
#include "Logger.h"

#include <Recognizer.h>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {

  World::getInstance()->initWorld(320, 240);
  VideoFactory::getInstance()->addVideoSource("cam", 0);
  
  // Main loop
  while (EndController::getInstance()->isRunning()) {
    // Grab a frame from the camera!
    VideoFactory::getInstance()->getMainCamera().grabFrame();
    
    // Poll the events
    InputEventController::getInstance()->pollEvents();

    // Detection Logic
    cv::Mat* frame = VideoFactory::getInstance()->getInstance()->getMainCamera().getLastFrame();
    Recognizer::getInstance()->detect(*frame);


    // Print the results, if any
    //std::string& result = GestureRecognizer::getInstance()->getRecognizedGesture();
    //if(result != "") std::cout<<result<<endl;

    // Draw
    World::getInstance()->drawWorld();
  }
  
  //Freeing resources
  World::getInstance()->destroy();
  Recognizer::getInstance()->destroy();
  VideoFactory::getInstance()->destroy();
  
  return 0;
}
