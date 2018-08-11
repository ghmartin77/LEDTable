/*
 * FallingObjectsVisualizer.cpp
 *
 *  Created on: 27.08.2016
 *      Author: anonymous
 */

#include <math.h>
#include "FallingObjectsVisualizer.h"

FallingObjectsVisualizer::FallingObjectsVisualizer(uint8_t direction) :
		foDirection(direction) {
}

FallingObjectsVisualizer::~FallingObjectsVisualizer() {
}

void FallingObjectsVisualizer::computeImage() {
	if (foRandomColor) {
		if (foCounter > foRandomIntervall) {
			foRedValue = (uint8_t) random(256);
			foGreenValue = (uint8_t) random(256);
			foBlueValue = (uint8_t) random(256);
			foCounter = 0;
		} else {
			foCounter += 1;
		}
	}

	switch (foDirection) {
	case 0:
		moveDown();
		break;
	case 1:
		moveUp();
		break;
	case 2:
		moveRight();
		break;
	case 3:
		moveLeft();
		break;
	}
}

void FallingObjectsVisualizer::moveDown() {
	for (uint8_t x = 0; x < 12 * 3; x++) {
		for (uint8_t y = 1; y < 12; y++) {
			imageData[((12 - y) * 36 + x)] = imageData[((12 - y - 1) * 36 + x)];
		}
	}

	for (uint8_t x = 0; x < 12; x++) {
		uint8_t ra = (uint8_t) random(100);

		if (ra < foNumber) {
			foIsActive[x] = true;
			foPosition[x] = 0;
		}

		if (foIsActive[x] != 0) {
			int r = foRedValue
					- foPosition[x] * (int) floor(foRedValue / foLength);
			int g = foGreenValue
					- foPosition[x] * (int) floor(foGreenValue / foLength);
			int b = foBlueValue
					- foPosition[x] * (int) floor(foBlueValue / foLength);

			if (r > 255)
				r = 255;
			if (g > 255)
				g = 255;
			if (b > 255)
				b = 255;

			if (r < 0)
				r = 0;
			if (g < 0)
				g = 0;
			if (b < 0)
				b = 0;

			imageData[x * 3] = (uint8_t) r;
			imageData[x * 3 + 1] = (uint8_t) g;
			imageData[x * 3 + 2] = (uint8_t) b;

			foPosition[x] += 1;

			if (foPosition[x] > foLength) {
				foIsActive[x] = false;
				foPosition[x] = 0;
			}

		} else {
			imageData[x * 3] = 0;
			imageData[x * 3 + 1] = 0;
			imageData[x * 3 + 2] = 0;
		}
	}
}

void FallingObjectsVisualizer::moveRight() {
	for (uint8_t x = 1 * 3; x < 12 * 3; x++) {
		for (uint8_t y = 0; y < 12; y++) {
			imageData[y * 36 + (12 * 3 - x + 2)] = imageData[y * 36
					+ (12 * 3 - x - 1)];
		}
	}

	for (uint8_t y = 0; y < 12; y++) {
		uint8_t ra = (uint8_t) random(100);

		if (ra < foNumber) {
			foIsActive[y] = true;
			foPosition[y] = 0;
		}

		if (foIsActive[y] != 0) {
			int r = foRedValue
					- foPosition[y] * (int) floor(foRedValue / foLength);
			int g = foGreenValue
					- foPosition[y] * (int) floor(foGreenValue / foLength);
			int b = foBlueValue
					- foPosition[y] * (int) floor(foBlueValue / foLength);

			if (r > 255)
				r = 255;
			if (g > 255)
				g = 255;
			if (b > 255)
				b = 255;

			if (r < 0)
				r = 0;
			if (g < 0)
				g = 0;
			if (b < 0)
				b = 0;

			imageData[y * 36] = (uint8_t) r;
			imageData[y * 36 + 1] = (uint8_t) g;
			imageData[y * 36 + 2] = (uint8_t) b;

			foPosition[y] += 1;

			if (foPosition[y] > foLength) {
				foIsActive[y] = false;
				foPosition[y] = 0;
			}

		} else {
			imageData[y * 36] = 0;
			imageData[y * 36 + 1] = 0;
			imageData[y * 36 + 2] = 0;
		}
	}
}

void FallingObjectsVisualizer::moveLeft() {
	for (uint8_t x = 0; x < (12 - 1) * 3; x++) {
		for (uint8_t y = 0; y < 12; y++) {
			imageData[y * 36 + x] = imageData[y * 36 + x + 3];
		}
	}

	for (uint8_t y = 0; y < 12; y++) {
		uint8_t ra = (uint8_t) random(100);

		if (ra < foNumber) {
			foIsActive[y] = true;
			foPosition[y] = 0;
		}

		if (foIsActive[y] != 0) {
			int r = foRedValue
					- foPosition[y] * (int) floor(foRedValue / foLength);
			int g = foGreenValue
					- foPosition[y] * (int) floor(foGreenValue / foLength);
			int b = foBlueValue
					- foPosition[y] * (int) floor(foBlueValue / foLength);

			if (r > 255)
				r = 255;
			if (g > 255)
				g = 255;
			if (b > 255)
				b = 255;

			if (r < 0)
				r = 0;
			if (g < 0)
				g = 0;
			if (b < 0)
				b = 0;

			imageData[y * 36 + 33] = (uint8_t) r;
			imageData[y * 36 + 34] = (uint8_t) g;
			imageData[y * 36 + 35] = (uint8_t) b;

			foPosition[y] += 1;

			if (foPosition[y] > foLength) {
				foIsActive[y] = false;
				foPosition[y] = 0;
			}

		} else {
			imageData[y * 36 + 33] = 0;
			imageData[y * 36 + 34] = 0;
			imageData[y * 36 + 35] = 0;
		}
	}
}

void FallingObjectsVisualizer::moveUp() {
	for (uint8_t x = 0; x < 12 * 3; x++) {
		for (uint8_t y = 0; y < 11; y++) {
			imageData[(y * 36 + x)] = imageData[(y + 1) * 36 + x];
		}
	}

	for (uint8_t x = 0; x < 12; x++) {
		uint8_t ra = (uint8_t) random(100);

		if (ra < foNumber) {
			foIsActive[x] = true;
			foPosition[x] = 0;
		}

		if (foIsActive[x] != 0) {
			int r = foRedValue
					- foPosition[x] * (int) floor(foRedValue / foLength);
			int g = foGreenValue
					- foPosition[x] * (int) floor(foGreenValue / foLength);
			int b = foBlueValue
					- foPosition[x] * (int) floor(foBlueValue / foLength);

			if (r > 255)
				r = 255;
			if (g > 255)
				g = 255;
			if (b > 255)
				b = 255;

			if (r < 0)
				r = 0;
			if (g < 0)
				g = 0;
			if (b < 0)
				b = 0;

			imageData[((12 - 1) * 36) + x * 3] = (uint8_t) r;
			imageData[((12 - 1) * 36) + x * 3 + 1] = (uint8_t) g;
			imageData[((12 - 1) * 36) + x * 3 + 2] = (uint8_t) b;

			foPosition[x] += 1;

			if (foPosition[x] > foLength) {
				foIsActive[x] = false;
				foPosition[x] = 0;
			}

		} else {
			imageData[((12 - 1) * 36) + x * 3] = 0;
			imageData[((12 - 1) * 36) + x * 3 + 1] = 0;
			imageData[((12 - 1) * 36) + x * 3 + 2] = 0;
		}
	}
}

void FallingObjectsVisualizer::start() {
	randomSeed(micros());
}

void FallingObjectsVisualizer::stop() {
}

void FallingObjectsVisualizer::onButtonPressed(uint8_t button, uint8_t buttonStates) {
	switch (button) {
	case 1:
		foLength -= 1;
		if (foLength <= 1)
			foLength = 1;
		break;
	case 2:
		foLength += 1;
		if (foLength > 30)
			foLength = 30;
		break;
	case 3:
		foRandomIntervall -= 5;
		if (foRandomIntervall <= 1)
			foRandomIntervall = 1;
		break;
	case 4:
		foRandomIntervall += 5;
		if (foRandomIntervall > 100)
			foRandomIntervall = 100;
		break;
	}
}
