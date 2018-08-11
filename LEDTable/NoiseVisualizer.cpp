/*
 * NoiseVisualizer.cpp
 *
 *  Created on: 22.08.2016
 *      Author: anonymous
 */

#include "NoiseVisualizer.h"

NoiseVisualizer::NoiseVisualizer() {
}

NoiseVisualizer::~NoiseVisualizer() {
}

void NoiseVisualizer::computeImage() {
	for (int i = 0; i < 12; i++) {
		int ioffset = scale * i;
		for (int j = 0; j < 12; j++) {
			int joffset = scale * j;
			noise[i][j] = inoise8(x + ioffset, y + joffset, z);
		}
	}
	z += speed;

	CRGB crgb;

	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			// You can also explore other ways to constrain the hue used, like below
			// CHSV chsv = CHSV(ihue + (noise[j][i]>>2),255,noise[i][j]);
			CHSV chsv = CHSV(noise[j][i], 255, noise[i][j]);
			hsv2rgb_rainbow(chsv, crgb);

			imageData[i * 3 + 0 + j * 12 * 3] = crgb.r;
			imageData[i * 3 + 1 + j * 12 * 3] = crgb.g;
			imageData[i * 3 + 2 + j * 12 * 3] = crgb.b;
		}
	}
	ihue += 1;
}

void NoiseVisualizer::start() {
	x = random16();
	y = random16();
	z = random16();
}

void NoiseVisualizer::stop() {
}

void NoiseVisualizer::onButtonPressed(uint8_t button, uint8_t buttonStates) {
	switch (button) {
	case 1:
		speed -= 1;
		if (speed <= 1)
			speed = 1;
		break;
	case 2:
		speed += 1;
		if (speed >= 60)
			speed = 60;
		break;
	case 3:
		scale -= 3;
		if (scale <= 4)
			scale = 4;
		break;
	case 4:
		scale += 3;
		if (scale >= 100)
			scale = 100;
		break;
	}
}
