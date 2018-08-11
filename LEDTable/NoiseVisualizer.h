/*
 * NoiseVisualizer.h
 *
 *  Created on: 22.08.2016
 *      Author: anonymous
 */

#ifndef NOISEVISUALIZER_H_
#define NOISEVISUALIZER_H_

#define FASTLED_INTERNAL

#include "Visualizer.h"
#include "FastLED.h"

class NoiseVisualizer: public Visualizer {
public:
	NoiseVisualizer();
	virtual ~NoiseVisualizer();

	virtual void start();
	virtual void stop();

	virtual void onButtonPressed(uint8_t button, uint8_t buttonStates);

protected:
	virtual void computeImage();

private:
	uint16_t x = 0;
	uint16_t y = 0;
	uint16_t z = 0;

	uint16_t scale = 10;

	uint8_t noise[12][12];
	uint16_t speed = 5;
	uint8_t ihue = 0;
};

#endif /* NOISEVISUALIZER_H_ */
