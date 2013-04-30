/*
 * TrackingMethod.cpp
 *
 *  Created on: 20/02/2011
 *      Author: cesar
 */

#include <Kernel/TrackingMethods/TrackingMethod.h>

TrackingMethod::TrackingMethod() {
	_active = true;
}

bool TrackingMethod::isActive() {
	return _active;
}
void TrackingMethod::active() {
	_active = true;
}
void TrackingMethod::deactive() {
	_active = false;
}
TrackingMethod::~TrackingMethod() {
}
