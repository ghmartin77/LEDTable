/*
 * NoneApp.cpp
 *
 *  Created on: 23.07.2016
 *      Author: anonymous
 */

#include "NoneApp.h"

NoneApp::NoneApp(LEDMatrix* pLEDMatrix) :
		App(pLEDMatrix) {
	name = "Nothing (Off)";
}

NoneApp::~NoneApp() {
}

void NoneApp::start() {
	pMatrix->clear();
}

void NoneApp::run() {
	unsigned long int currentMillis = millis();

	if (currentMillis - 1000 < lastMillis) {
		yield();
		return;
	}

	lastMillis = currentMillis;
	pMatrix->clear();
}
