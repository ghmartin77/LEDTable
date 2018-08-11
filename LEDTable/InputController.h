/*
 * InputController.h
 *
 *  Created on: 30.07.2016
 *      Author: anonymous
 */

#ifndef INPUTCONTROLLER_H_
#define INPUTCONTROLLER_H_

#include <Arduino.h>
#include "defines.h"
#include "CapacitiveButton.h"

class InputController {
public:
	InputController();
	virtual ~InputController();

	void update();
	inline void setEventCallback(void (*fptr)(uint8_t* eventData)) {
		eventCallback = fptr;
	}

private:
	void (*eventCallback)(uint8_t* data);

	CapacitiveButton buttons[4] = { CapacitiveButton(D6, BUTTON_SAMPLES, 90),
			CapacitiveButton(D5, BUTTON_SAMPLES, 90), CapacitiveButton(D2,
					BUTTON_SAMPLES, 70), CapacitiveButton(D1, BUTTON_SAMPLES,
					80) };

	bool buttonState[2][4] = { { false, false, false, false }, { false, false,
	false, false } };

	unsigned long buttonPressTime[4] = { 0, 0, 0, 0 };
	unsigned long lastMillis;
	uint8_t buttonReleaseCounter[4] = { 1, 1, 1, 1 };

	static uint8_t eb1[];
	static uint8_t eb2[];
	static uint8_t eb3[];
	static uint8_t eb4[];

	static uint8_t eAllButtons[];

	uint8_t stateIdx;
};

#endif /* INPUTCONTROLLER_H_ */
