/*
 * RotatingRainbowVisualizer.cpp
 *
 *  Created on: 22.08.2016
 *      Author: anonymous
 */

#include "RotatingRainbowVisualizer.h"

RotatingRainbowVisualizer::RotatingRainbowVisualizer() {
}

RotatingRainbowVisualizer::~RotatingRainbowVisualizer() {
}

void RotatingRainbowVisualizer::computeImage() {
	uint32_t ms = millis();
	int32_t yHueDelta32 = ((int32_t) cos16(ms * cosy) * (350 / 12));
	int32_t xHueDelta32 = ((int32_t) cos16(ms * cosx) * (310 / 12));
	byte startHue8 = ms / 65536;
	int8_t yHueDelta8 = yHueDelta32 / 32768;
	int8_t xHueDelta8 = xHueDelta32 / 32768;

	CRGB crgb;

	byte lineStartHue = startHue8;
	for (byte y = 0; y < 12; y++) {
		lineStartHue += yHueDelta8;
		byte pixelHue = lineStartHue;
		for (byte x = 0; x < 12; x++) {
			pixelHue += xHueDelta8;
			CHSV chsv = CHSV(pixelHue, 255, 255);
			hsv2rgb_rainbow(chsv, crgb);

			imageData[x * 3 + 0 + y * 12 * 3] = crgb.r;
			imageData[x * 3 + 1 + y * 12 * 3] = crgb.g;
			imageData[x * 3 + 2 + y * 12 * 3] = crgb.b;
		}
	}

}

void RotatingRainbowVisualizer::start() {
}

void RotatingRainbowVisualizer::stop() {
}

void RotatingRainbowVisualizer::onButtonPressed(uint8_t button,
		uint8_t buttonStates) {
	switch (button) {
	case 1:
		cosy -= 1;
		if (cosy <= 1)
			cosy = 1;
		break;
	case 2:
		cosy += 1;
		if (cosy >= 60)
			cosy = 60;
		break;
	case 3:
		cosx -= 1;
		if (cosx <= 1)
			cosx = 1;
		break;
	case 4:
		cosx += 1;
		if (cosx >= 60)
			cosx = 60;
		break;
	}
}
