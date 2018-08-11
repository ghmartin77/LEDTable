/*
 * CapacitiveButton.h
 *
 *  Created on: 29.07.2016
 *      Author: anonymous
 */

#ifndef CAPACITIVEBUTTON_H_
#define CAPACITIVEBUTTON_H_

#include <Arduino.h>

class CapacitiveButton {
public:
	CapacitiveButton(uint8_t aPin, uint8_t aSamples, uint8_t aThreshold);
	virtual ~CapacitiveButton();

	bool poll();

private:
	uint8_t pin;
	uint8_t samples;
	uint8_t threshold;
};

#endif /* CAPACITIVEBUTTON_H_ */
