/*
 * App.h
 *
 *  Created on: 23.07.2016
 *      Author: anonymous
 */

#ifndef APP_H_
#define APP_H_

#include "LEDMatrix.h"

class App {
public:
	App(LEDMatrix* pLEDMatrix);
	virtual ~App();

	virtual void start() {
	}

	virtual void stop() {
	}

	virtual void onButtonPressed(uint8_t button, uint8_t buttonStates) {
	}

	virtual void run() = 0;

	const char* getName() const {
		return name;
	}

protected:
	const char* name;
	LEDMatrix *pMatrix;
};

#endif /* APP_H_ */
