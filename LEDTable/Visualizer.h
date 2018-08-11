/*
 * Visualizer.h
 *
 *  Created on: 21.08.2016
 *      Author: anonymous
 */

#ifndef VISUALIZER_H_
#define VISUALIZER_H_

#include <Arduino.h>

class Visualizer {
public:
	Visualizer();
	virtual ~Visualizer();

	virtual void start() {
	}

	virtual void stop() {
	}

	uint8_t* renderNextImage();

	virtual void onButtonPressed(uint8_t button, uint8_t buttonStates) {
	}

protected:
	int8_t speed;
	int8_t speedCounter;

	uint8_t imageData[12 * 12 * 3];

	virtual void computeImage() = 0;
};

#endif /* VISUALIZER_H_ */
