/*
 * TestPatternApp.h
 *
 *  Created on: 27.08.2016
 *      Author: anonymous
 */

#ifndef TESTPATTERNAPP_H_
#define TESTPATTERNAPP_H_

#include "App.h"

class TestPatternApp: public App {
public:
	TestPatternApp(LEDMatrix* pLEDMatrix);
	virtual ~TestPatternApp();

	virtual void start();
	virtual void run();
	virtual void stop();

	virtual void onButtonPressed(uint8_t button, uint8_t buttonStates);

private:
	float brightness = 1.0f;
	int8_t patternType = 0;

	void renderTestPattern();
};

#endif /* TESTPATTERNAPP_H_ */
