/*
 * LEDMatrix.h
 *
 *  Created on: 21.07.2016
 *      Author: anonymous
 */

#ifndef LEDMATRIX_H_
#define LEDMATRIX_H_

#define MATRIX_SIZE 12
#define MATRIX_RGB_FORMAT WS2801_RBG

#include <Adafruit_WS2801.h>

class LEDMatrix {
public:
	enum Rotation {ROTATION_0, ROTATION_90, ROTATION_180, ROTATION_270};

	LEDMatrix(uint8_t dpin, uint8_t cpin);
	virtual ~LEDMatrix();

	void init();

	void setPixel(int16_t x, int16_t y, uint8_t r, uint8_t g, uint8_t b);
	void setPixel(int16_t x, int16_t y, uint32_t rgb);
	uint32_t getPixel(int16_t x, int16_t y);

	void clear(boolean update=true);
	void fill(uint8_t r, uint8_t g, uint8_t b, boolean updateMatrix=true);
	void update();

	void rotateCW();
	void rotateCCW();

	void setRotation(Rotation rot);
	void setCalibration(float r, float g, float b);
	void setBrightness(float percentage);
	float getBrightness();

private:
	Adafruit_WS2801 matrix;

	uint8_t *pixels;

	Rotation rotation = ROTATION_0;

	float calibrationRed = 1.0f;
	float calibrationGreen = 1.0f;
	float calibrationBlue = 1.0f;
	float brightness = 1.0f;
};

#endif /* LEDMATRIX_H_ */
