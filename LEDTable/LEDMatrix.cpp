/*
 * LEDMatrix.cpp
 *
 *  Created on: 21.07.2016
 *      Author: anonymous
 */

#include "LEDMatrix.h"

LEDMatrix::LEDMatrix(uint8_t dpin, uint8_t cpin) :
		matrix(Adafruit_WS2801(MATRIX_SIZE, MATRIX_SIZE, dpin, cpin,
		MATRIX_RGB_FORMAT)), pixels(
				(uint8_t*) malloc(3 * MATRIX_SIZE * MATRIX_SIZE)) {

}

LEDMatrix::~LEDMatrix() {
	if (pixels)
		free(pixels);
}

void LEDMatrix::init() {
	matrix.begin();
}

void LEDMatrix::clear(boolean update) {
	fill(0, 0, 0, update);
}

void LEDMatrix::fill(uint8_t r, uint8_t g, uint8_t b, boolean updateMatrix) {
	for (uint16_t i = 0; i < MATRIX_SIZE * MATRIX_SIZE * 3; i += 3) {
		pixels[i] = r;
		pixels[i + 1] = g;
		pixels[i + 2] = b;
	}
	if (updateMatrix)
		update();
}

void LEDMatrix::setPixel(int16_t x, int16_t y, uint8_t r, uint8_t g,
		uint8_t b) {
	if (x >= MATRIX_SIZE || y >= MATRIX_SIZE || x < 0 || y < 0)
		return;

	uint16_t idx = (x + y * MATRIX_SIZE) * 3;
	pixels[idx] = r;
	pixels[idx + 1] = g;
	pixels[idx + 2] = b;
}

void LEDMatrix::setPixel(int16_t x, int16_t y, uint32_t rgb) {
	if (x >= MATRIX_SIZE || y >= MATRIX_SIZE || x < 0 || y < 0)
		return;

	uint16_t idx = (x + y * MATRIX_SIZE) * 3;
	pixels[idx] = (rgb >> 16) & 0xff;
	pixels[idx + 1] = (rgb >> 8) & 0xff;
	pixels[idx + 2] = rgb & 0xff;
}

uint32_t LEDMatrix::getPixel(int16_t x, int16_t y) {
	if (x >= MATRIX_SIZE || y >= MATRIX_SIZE || x < 0 || y < 0)
		return 0xff000000;
	uint16_t idx = (x + y * MATRIX_SIZE) * 3;
	return pixels[idx] << 16 || pixels[idx + 1] << 8 || pixels[idx + 2];
}

void LEDMatrix::setRotation(Rotation rot) {
	rotation = rot;
}

void LEDMatrix::setCalibration(float r, float g, float b) {
	calibrationRed = r;
	calibrationGreen = g;
	calibrationBlue = b;
}

void LEDMatrix::setBrightness(float percentage) {
	brightness = percentage;
}

float LEDMatrix::getBrightness() {
	return brightness;
}

void LEDMatrix::update() {
	uint16_t x = 0;
	uint16_t y = 0;

	float calibrationRedEffectively = calibrationRed * brightness;
	float calibrationGreenEffectively = calibrationGreen * brightness;
	float calibrationBlueEffectively = calibrationBlue * brightness;

	if (rotation == ROTATION_90) {
		for (uint16_t idx = 0; idx < MATRIX_SIZE * MATRIX_SIZE * 3;
				idx = idx + 3) {
			matrix.setPixelColor(MATRIX_SIZE - 1 - y, x,
					pixels[idx] * calibrationRedEffectively,
					pixels[idx + 1] * calibrationGreenEffectively,
					pixels[idx + 2] * calibrationBlueEffectively);
			if (++x >= MATRIX_SIZE) {
				++y;
				x = 0;
			}
		}
	} else if (rotation == ROTATION_180) {
		for (uint16_t idx = 0; idx < MATRIX_SIZE * MATRIX_SIZE * 3;
				idx = idx + 3) {

			matrix.setPixelColor(MATRIX_SIZE - 1 - x, MATRIX_SIZE - 1 - y,
					pixels[idx] * calibrationRedEffectively,
					pixels[idx + 1] * calibrationGreenEffectively,
					pixels[idx + 2] * calibrationBlueEffectively);
			if (++x >= MATRIX_SIZE) {
				++y;
				x = 0;
			}
		}
	} else if (rotation == ROTATION_270) {
		for (uint16_t idx = 0; idx < MATRIX_SIZE * MATRIX_SIZE * 3;
				idx = idx + 3) {
			matrix.setPixelColor(y, MATRIX_SIZE - 1 - x,
					pixels[idx] * calibrationRedEffectively,
					pixels[idx + 1] * calibrationGreenEffectively,
					pixels[idx + 2] * calibrationBlueEffectively);
			if (++x >= MATRIX_SIZE) {
				++y;
				x = 0;
			}
		}
	} else { // ROTATION_0
		for (uint16_t idx = 0; idx < MATRIX_SIZE * MATRIX_SIZE * 3;
				idx = idx + 3) {
			matrix.setPixelColor(x, y, pixels[idx] * calibrationRedEffectively,
					pixels[idx + 1] * calibrationGreenEffectively,
					pixels[idx + 2] * calibrationBlueEffectively);
			if (++x >= MATRIX_SIZE) {
				++y;
				x = 0;
			}
		}
	}
	matrix.show();
}

void LEDMatrix::rotateCW() {
	switch (rotation) {
	case ROTATION_0:
		setRotation(ROTATION_90);
		break;
	case ROTATION_90:
		setRotation(ROTATION_180);
		break;
	case ROTATION_180:
		setRotation(ROTATION_270);
		break;
	default:
		setRotation(ROTATION_0);
		break;
	}

	update();
}

void LEDMatrix::rotateCCW() {
	switch (rotation) {
	case ROTATION_0:
		setRotation(ROTATION_270);
		break;
	case ROTATION_90:
		setRotation(ROTATION_0);
		break;
	case ROTATION_180:
		setRotation(ROTATION_90);
		break;
	default:
		setRotation(ROTATION_180);
		break;
	}

	update();
}
