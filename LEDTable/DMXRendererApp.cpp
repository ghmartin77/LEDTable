/*
 * DMXRendererApp.cpp
 *
 *  Created on: 23.07.2016
 *      Author: anonymous
 */

#include "DMXRendererApp.h"

LEDMatrix* DMXRendererApp::pLEDMATRIX = NULL;

void DMXRendererApp::onDmxFrame(uint16_t universe, uint16_t length,
		uint8_t sequence, uint8_t* data) {
	int pixel = 0;
	uint16_t x = 0, y = 0;
	for (int i = 0; i < length; i += 3) {
		pLEDMATRIX->setPixel(x, y, data[i], data[i + 1], data[i + 2]);
		if (++x >= MATRIX_SIZE) {
			++y;
			x = 0;
		}
	}

	pLEDMATRIX->update();
}

DMXRendererApp::~DMXRendererApp() {
}

DMXRendererApp::DMXRendererApp(LEDMatrix* pLEDMatrix) :
		App(pLEDMatrix) {
	name = "DMXRenderer";

	DMXRendererApp::pLEDMATRIX = pLEDMatrix;

	artnet.setArtDmxCallback(DMXRendererApp::onDmxFrame);
}

void DMXRendererApp::run() {
	artnet.read();
}

void DMXRendererApp::start() {
	pMatrix->clear();

	artnet.begin();
}

void DMXRendererApp::stop() {
	artnet.stop();
}

void DMXRendererApp::onButtonPressed(uint8_t button, uint8_t buttonStates) {
	// disable calibration
	if (true)
		return;

	switch (button) {
	case 1:
		calR -= 0.1;
		if (calR <= 0)
			calR = 1.0;
		pMatrix->setCalibration(calR, calG, calB);
		break;
	case 2:
		calG -= 0.1;
		if (calG <= 0)
			calG = 1.0;
		pMatrix->setCalibration(calR, calG, calB);
		break;
	case 3:
		calB -= 0.1;
		if (calB <= 0)
			calB = 1.0;
		pMatrix->setCalibration(calR, calG, calB);
		break;
	case 4:
		Serial.println(
				"calR:" + String(calR) + ", calG:" + String(calG) + ", calB:"
						+ String(calB));
		break;
	}
}

