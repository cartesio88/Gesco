/*
 * Singleton.h
 *
 *  Created on: 20/02/2011
 *      Author: cesar
 */

#ifndef SINGLETON_H_
#define SINGLETON_H_

#include<iostream>
#include <cstdlib>

template<typename T>
class Singleton {
public:


public:
	static T* getInstance() {
		if (_instance == NULL) {
			_instance = new T;
		}
		return _instance;
	}

	static void destroy() {
	  if(_instance!=NULL) delete _instance;
	}

private:
	static T* _instance;

	Singleton & operator=(const Singleton &);

	
};

template<typename T>
T* Singleton<T>::_instance = NULL;

#endif /* SINGLETON_H_ */
