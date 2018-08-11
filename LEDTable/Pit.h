/*
 * Pit.h
 *
 *  Created on: 24.07.2016
 *      Author: anonymous
 */

#ifndef PIT_H_
#define PIT_H_

#include "LEDMatrix.h"

class Pit {
public:
	Pit();
	virtual ~Pit();

	void draw(LEDMatrix *pMatrix);
	void clear();

	uint8_t get(uint8_t x, uint8_t y);
	void set(uint8_t x, uint8_t y, uint8_t val);

	void rollUp();

	void dump();

private:
	uint8_t data[10][12];
};

#endif /* PIT_H_ */
