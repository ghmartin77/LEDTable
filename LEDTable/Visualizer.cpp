/*
 * Visualizer.cpp
 *
 *  Created on: 21.08.2016
 *      Author: anonymous
 */

#include "Visualizer.h"

Visualizer::Visualizer() :
		speed(0), speedCounter(0) {
	memset(imageData, 0, sizeof(imageData));
}

Visualizer::~Visualizer() {
}

uint8_t* Visualizer::renderNextImage() {
	if (speedCounter == 0) {
		computeImage();
	}

	if (speedCounter++ >= speed) {
		speedCounter = 0;
	}

	return imageData;
}
