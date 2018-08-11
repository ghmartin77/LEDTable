/*
 * NoiseWithPaletteVisualizer.cpp
 *
 *  Created on: 22.08.2016
 *      Author: anonymous
 */

#include "NoiseWithPaletteVisualizer.h"

NoiseWithPaletteVisualizer::NoiseWithPaletteVisualizer() :
		currentPalette(PartyColors_p) {
}

NoiseWithPaletteVisualizer::~NoiseWithPaletteVisualizer() {
}

void NoiseWithPaletteVisualizer::computeImage() {
	// generate noise data
	fillnoise8();

	// convert the noise data to colors in the LED array
	// using the current palette
	mapNoiseToLEDsUsingPalette();
}

void NoiseWithPaletteVisualizer::fillnoise8() {
	// If we're runing at a low "speed", some 8-bit artifacts become visible
	// from frame-to-frame.  In order to reduce this, we can do some fast data-smoothing.
	// The amount of data smoothing we're doing depends on "speed".
	uint8_t dataSmoothing = 0;
	if (speed < 50) {
		dataSmoothing = 200 - (speed * 4);
	}

	for (int i = 0; i < 12; i++) {
		int ioffset = scale * i;
		for (int j = 0; j < 12; j++) {
			int joffset = scale * j;

			uint8_t data = inoise8(x + ioffset, y + joffset, z);

			// The range of the inoise8 function is roughly 16-238.
			// These two operations expand those values out to roughly 0..255
			// You can comment them out if you want the raw noise data.
			data = qsub8(data, 16);
			data = qadd8(data, scale8(data, 39));

			if (dataSmoothing) {
				uint8_t olddata = noise[i][j];
				uint8_t newdata = scale8(olddata, dataSmoothing)
						+ scale8(data, 256 - dataSmoothing);
				data = newdata;
			}

			noise[i][j] = data;
		}
	}

	z += speed;

	// apply slow drift to X and Y, just for visual variation.
	x += speed / 8;
	y -= speed / 16;
}

void NoiseWithPaletteVisualizer::mapNoiseToLEDsUsingPalette() {
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			// We use the value at the (i,j) coordinate in the noise
			// array for our brightness, and the flipped value from (j,i)
			// for our pixel's index into the color palette.

			uint8_t index = noise[j][i];
			uint8_t bri = noise[i][j];

			// if this palette is a 'loop', add a slowly-changing base value
			if (colorLoop) {
				index += ihue;
			}

			// brighten up, as the color palette itself often contains the
			// light/dark dynamic range desired
			if (bri > 127) {
				bri = 255;
			} else {
				bri = dim8_raw(bri * 2);
			}

			CRGB crgb = ColorFromPalette(currentPalette, index, bri);
			imageData[i * 3 + 0 + j * 12 * 3] = crgb.r;
			imageData[i * 3 + 1 + j * 12 * 3] = crgb.g;
			imageData[i * 3 + 2 + j * 12 * 3] = crgb.b;
		}
	}

	ihue += 1;
}

// There are several different palettes of colors demonstrated here.
//
// FastLED provides several 'preset' palettes: RainbowColors_p, RainbowStripeColors_p,
// OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
//
// Additionally, you can manually define your own color palettes, or you can write
// code that creates color palettes on the fly.
// 1 = 5 sec per palette
// 2 = 10 sec per palette
// etc
#define HOLD_PALETTES_X_TIMES_AS_LONG 1

void NoiseWithPaletteVisualizer::applyProfile() {
	if (profile == 1) {
		currentPalette = RainbowColors_p;
		speed = 10;
		scale = 30;
		colorLoop = 1;
	} else if (profile == 2) {
		SetupPurpleAndGreenPalette();
		speed = 10;
		scale = 30;
		colorLoop = 1;
	} else if (profile == 3) {
		SetupBlackAndWhiteStripedPalette();
		speed = 10;
		scale = 30;
		colorLoop = 1;
	} else if (profile == 4) {
		currentPalette = ForestColors_p;
		speed = 8;
		scale = 20;
		colorLoop = 0;
	} else if (profile == 5) {
		currentPalette = CloudColors_p;
		speed = 4;
		scale = 30;
		colorLoop = 0;
	} else if (profile == 6) {
		currentPalette = LavaColors_p;
		speed = 8;
		scale = 10;
		colorLoop = 0;
	} else if (profile == 7) {
		currentPalette = OceanColors_p;
		speed = 10;
		scale = 20;
		colorLoop = 0;
	} else if (profile == 8) {
		currentPalette = PartyColors_p;
		speed = 10;
		scale = 30;
		colorLoop = 1;
	} else if (profile == 9) {
		currentPalette = RainbowStripeColors_p;
		speed = 5;
		scale = 15;
		colorLoop = 1;
	}
}

// This function generates a random palette that's a gradient between four different colors.  The first is a dim hue, the second is
// a bright hue, the third is a bright pastel, and the last is
// another bright hue.  This gives some visual bright/dark variation
// which is more interesting than just a gradient of different hues.
void NoiseWithPaletteVisualizer::SetupRandomPalette() {
	currentPalette = CRGBPalette16(CHSV(random8(), 255, 32),
			CHSV(random8(), 255, 255), CHSV(random8(), 128, 255),
			CHSV(random8(), 255, 255));
}

// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
void NoiseWithPaletteVisualizer::SetupBlackAndWhiteStripedPalette() {
// 'black out' all 16 palette entries...
	fill_solid(currentPalette, 16, CRGB::Black);
// and set every fourth one to white.
	currentPalette[0] = CRGB::White;
	currentPalette[4] = CRGB::White;
	currentPalette[8] = CRGB::White;
	currentPalette[12] = CRGB::White;

}

// This function sets up a palette of purple and green stripes.
void NoiseWithPaletteVisualizer::SetupPurpleAndGreenPalette() {
	CRGB purple = CHSV(HUE_PURPLE, 255, 255);
	CRGB green = CHSV(HUE_GREEN, 255, 255);
	CRGB black = CRGB::Black;

	currentPalette = CRGBPalette16(green, green, black, black, purple, purple,
			black, black, green, green, black, black, purple, purple, black,
			black);
}

void NoiseWithPaletteVisualizer::start() {
	x = random16();
	y = random16();
	z = random16();
}

void NoiseWithPaletteVisualizer::stop() {
}

void NoiseWithPaletteVisualizer::onButtonPressed(uint8_t button,
		uint8_t buttonStates) {
	switch (button) {
	case 1:
		if ((buttonStates & 2) == 2) {
			if (++profile >= 10)
				profile = 1;
			applyProfile();
		} else {
			speed -= 1;
			if (speed <= 1)
				speed = 1;
		}
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
