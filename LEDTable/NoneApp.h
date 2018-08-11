/*
 * NoneApp.h
 *
 *  Created on: 23.07.2016
 *      Author: anonymous
 */

#ifndef NONEAPP_H_
#define NONEAPP_H_

#include "App.h"

class NoneApp: public App {
public:
	NoneApp(LEDMatrix* pLEDMatrix);
	virtual ~NoneApp();

	virtual void start();
	virtual void run();

private:
	unsigned long int lastMillis = 0;

};

#endif /* NONEAPP_H_ */
