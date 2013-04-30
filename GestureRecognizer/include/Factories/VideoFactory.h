/*
 * VideoFactory.h
 *
 *  Created on: 20/02/2011
 *      Author: cesar
 */

#ifndef VIDEOFACTORY_H_
#define VIDEOFACTORY_H_

#include <Kernel/Singleton.h>
#include <Kernel/VideoSource.h>
#include <Kernel/Logger.h>
#include <string>
#include <vector>

class VideoFactory: public Singleton<VideoFactory> {
public:
	VideoFactory();
	void addVideoSource(const std::string& name, const int& nDevice);
	VideoSource& getCamera(const std::string& name);
	VideoSource& getMainCamera();
	void setMainCamera(const std::string& name);
	virtual ~VideoFactory();

private:
	std::vector<VideoSource*> _videoSources;
	VideoSource* _mainCamera;
};

#endif /* VIDEOFACTORY_H_ */
