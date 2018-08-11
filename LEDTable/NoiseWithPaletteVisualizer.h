/*
 * NoiseWithPaletteVisualizer.h
 *
 *  Created on: 22.08.2016
 *      Author: anonymous
 */

#ifndef NOISEWITHPALETTEVISUALIZER_H_
#define NOISEWITHPALETTEVISUALIZER_H_

#define FASTLED_INTERNAL

#include "Visualizer.h"
#include "FastLED.h"

class NoiseWithPaletteVisualizer: public Visualizer {
public:
	NoiseWithPaletteVisualizer();
	virtual ~NoiseWithPaletteVisualizer();

	virtual void start();
	virtual void stop();

	virtual void onButtonPressed(uint8_t button, uint8_t buttonStates);

protected:
	virtual void computeImage();

	void fillnoise8();
	void mapNoiseToLEDsUsingPalette();
	void applyProfile();
	void SetupRandomPalette();
	void SetupBlackAndWhiteStripedPalette();
	void SetupPurpleAndGreenPalette();

private:
	uint16_t x = 0;
	uint16_t y = 0;
	uint16_t z = 0;

	uint8_t profile = 1;

	uint8_t noise[12][12];
	uint16_t speed = 20;
	uint16_t scale = 30;
	CRGBPalette16 currentPalette;
	uint8_t colorLoop = 1;
	uint8_t ihue = 0;
};

#endif /* NOISEWITHPALETTEVISUALIZER_H_ */
