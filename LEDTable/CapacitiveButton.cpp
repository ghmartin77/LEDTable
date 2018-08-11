/*
 * CapacitiveButton.cpp
 *
 *  Created on: 29.07.2016
 *      Author: anonymous
 */

#include "CapacitiveButton.h"
#include "defines.h"

CapacitiveButton::CapacitiveButton(uint8_t aPin, uint8_t aSamples,
		uint8_t aThreshold) :
		pin(aPin), samples(aSamples), threshold(aThreshold) {
	pinMode(D7, OUTPUT);
}

CapacitiveButton::~CapacitiveButton() {
}

bool CapacitiveButton::poll() {
	uint16_t cycles = 0;
	uint8_t noSamples = 3;

	noInterrupts();
	while (noSamples > 0) {
		digitalWrite(D7, LOW);
		pinMode(pin, OUTPUT);
		digitalWrite(pin, LOW);
		delayMicroseconds(5);
		pinMode(pin, INPUT);
		digitalWrite(D7, HIGH);

		while (!digitalRead(pin) && cycles < 200) {
			cycles++;
		}
		noSamples--;
	}

	digitalWrite(pin, LOW);
	pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);

	interrupts();
#ifdef DEBUG
	if (cycles >= threshold) {
		TCPLOG(
				("Button " + String(pin) + " pressed (" + String(cycles)
						+ ")\r\n").c_str());
	}
#endif
	return cycles >= threshold;
}

