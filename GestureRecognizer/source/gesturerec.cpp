/*
 * gesturerec.cpp
 *
 *  Created on: 19/02/2011
 *      Author: cesar
 */
#include <Controllers/InputEventController.h>
#include <Controllers/HandDetector.h>
#include <Controllers/GestureRecognizer.h>
#include <Factories/VideoFactory.h>
#include <Kernel/VideoSource.h>
#include <Kernel/EndController.h>
#include <Kernel/World.h>
#include <Kernel/Logger.h>
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
    HandDetector::getInstance()->detect();
    GestureRecognizer::getInstance()->detect();

    // Print the results, if any
    std::string& result = GestureRecognizer::getInstance()->getRecognizedGesture();
    if(result != "") std::cout<<result<<endl;

    // Draw
    World::getInstance()->drawWorld();
  }
  
  //Freeing resources
  World::getInstance()->destroy();
  HandDetector::getInstance()->destroy();
  GestureRecognizer::getInstance()->destroy();
  VideoFactory::getInstance()->destroy();
  
  return 0;
}
