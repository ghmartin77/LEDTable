/*
 * Pit.cpp
 *
 *  Created on: 24.07.2016
 *      Author: anonymous
 */

#include "Pit.h"
#include "Shapes.h"

Pit::Pit() {
	clear();
}

Pit::~Pit() {
}

void Pit::draw(LEDMatrix *pMatrix) {
	for (int i = 0; i < 12; ++i) {
		pMatrix->setPixel(0, i, 160, 160, 160);
		pMatrix->setPixel(11, i, 160, 160, 160);
	}

	for (int x = 0; x < 10; ++x)
		for (int y = 0; y < 12; ++y) {
			pMatrix->setPixel(x + 1, y, shapeColors[data[x][y]][0],
					shapeColors[data[x][y]][1], shapeColors[data[x][y]][2]);
		}
}

void Pit::clear() {
	for (int x = 0; x < 10; ++x)
		for (int y = 0; y < 12; ++y) {
			data[x][y] = 0;
		}
}

uint8_t Pit::get(uint8_t x, uint8_t y) {
	return data[x][y];
}

void Pit::set(uint8_t x, uint8_t y, uint8_t val) {
	data[x][y] = val;
}

void Pit::rollUp() {
	int8_t x = -1;
	int8_t y = 11;

	while (y > 0) {
		if (x < 10) {
			x++;

			if (data[x][y] == 0) {
				y--;
				x = -1;
			}
			if (x == 9 && y > 0) {
				for (int8_t r = y; r > 0; --r) {
					for (int8_t c = 0; c < 10; ++c) {
						data[c][r] = data[c][r - 1];
					}
				}
				for (int8_t c = 0; c < 10; ++c) {
					data[c][0] = 0;
				}
				x = -1;
				y++;
			}
		}
	}
}

void Pit::dump() {
	Serial.println("Pit:");
	for (int y = 0; y < 12; ++y) {
		Serial.println();
		for (int x = 0; x < 10; ++x) {
			Serial.print(data[x][y]);
		}
	}
}

