/*
 * InputController.cpp
 *
 *  Created on: 30.07.2016
 *      Author: anonymous
 */

#include "InputController.h"

uint8_t InputController::eb1[] = { 3, 1, 0 };
uint8_t InputController::eb2[] = { 3, 2, 0 };
uint8_t InputController::eb3[] = { 3, 3, 0 };
uint8_t InputController::eb4[] = { 3, 4, 0 };
uint8_t InputController::eAllButtons[] = { 100 };

InputController::InputController() :
		eventCallback(NULL), stateIdx(0), lastMillis(0) {
}

InputController::~InputController() {
}

void InputController::update() {
	unsigned long currentMillis = millis();

	if (currentMillis < lastMillis + 25) {
		return;
	}

#ifdef DEBUG
	if (currentMillis - lastMillis > 40) {
		TCPLOG(("Updating Input deviation " + String(currentMillis - lastMillis) + "\r\n").c_str());
	}
#endif

	lastMillis = currentMillis;
	uint8_t lastStateIdx = stateIdx;
	if (++stateIdx > 1) {
		stateIdx = 0;
	}

	uint8_t buttonStates = 0;

	for (int i = 0; i < 4; ++i) {
		bool isButtonPressed = buttons[i].poll();

//		// Poll twice if switching from not pressed to pressed to filter glitches
//		if (isButtonPressed && !buttonState[lastStateIdx][i]) {
//			isButtonPressed = buttons[i].poll();
//		}

		buttonState[stateIdx][i] = buttonState[lastStateIdx][i];

		if (isButtonPressed) {
			//Serial.println("Button " + String(i) + " pressed");
			buttonStates |= (1 << i);
			buttonState[stateIdx][i] = true;
			buttonReleaseCounter[i] = 4;

			if (!buttonState[lastStateIdx][i]) {
				buttonPressTime[i] = currentMillis;
			}
		} else {
			if (buttonReleaseCounter[i] > 0) {
				buttonReleaseCounter[i]--;
			}
			if (buttonReleaseCounter[i] == 1) {
				buttonPressTime[i] = 0;

				buttonState[stateIdx][i] = false;
				buttonReleaseCounter[i] = 0;
			}
		}
	}

	if (buttonState[stateIdx][0] && buttonState[stateIdx][1]
			&& buttonState[stateIdx][2] && buttonState[stateIdx][3]) {
		eventCallback(eAllButtons);
		for (int i = 0; i < 4; ++i) {
			buttonState[stateIdx][i] = false;
			buttonReleaseCounter[i] = 0;
		}
	} else {
		if (buttonState[stateIdx][0] && (buttonPressTime[0] <= currentMillis)) {
			eb1[2] = buttonStates;
			eventCallback(eb1);
			buttonPressTime[0] = currentMillis + BUTTON_REPEAT_DELAY;
		}
		if (buttonState[stateIdx][1] && (buttonPressTime[1] <= currentMillis)) {
			eb2[2] = buttonStates;
			eventCallback(eb2);
			buttonPressTime[1] = currentMillis + BUTTON_REPEAT_DELAY;
		}
		if (buttonState[stateIdx][2] && (buttonPressTime[2] <= currentMillis)) {
			eb3[2] = buttonStates;
			eventCallback(eb3);
			buttonPressTime[2] = currentMillis + BUTTON_REPEAT_DELAY;
		}
		if (buttonState[stateIdx][3] && (buttonPressTime[3] <= currentMillis)) {
			eb4[2] = buttonStates;
			eventCallback(eb4);
			buttonPressTime[3] = currentMillis + BUTTON_REPEAT_DELAY;
		}
	}
}
