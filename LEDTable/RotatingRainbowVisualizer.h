/*
 * RotatingRainbowVisualizer.h
 *
 *  Created on: 22.08.2016
 *      Author: anonymous
 */

#ifndef ROTATINGRAINBOWVISUALIZER_H_
#define ROTATINGRAINBOWVISUALIZER_H_

#define FASTLED_INTERNAL

#include "Visualizer.h"
#include "FastLED.h"

class RotatingRainbowVisualizer: public Visualizer {
public:
	RotatingRainbowVisualizer();
	virtual ~RotatingRainbowVisualizer();

	virtual void start();
	virtual void stop();

	virtual void onButtonPressed(uint8_t button, uint8_t buttonStates);

protected:
	virtual void computeImage();

private:
	uint8_t cosx = 18;
	uint8_t cosy = 13;
};

#endif /* ROTATINGRAINBOWVISUALIZER_H_ */
