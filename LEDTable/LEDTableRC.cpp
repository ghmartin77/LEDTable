/*
 * LEDTableRC.cpp
 *
 *  Created on: 24.07.2016
 *      Author: anonymous
 */

#include "LEDTableRC.h"
#include <Arduino.h>

LEDTableRC::LEDTableRC() :
		eventCallback(NULL) {
}

LEDTableRC::~LEDTableRC() {
}

void LEDTableRC::begin() {
	udp.begin(UDP_PORT);
}

void LEDTableRC::update() {
	uint16_t packetSize = udp.parsePacket();

	if (packetSize <= MAX_BUFFER_RC && packetSize > 0) {
		udp.read(udpPacket, MAX_BUFFER_RC);

		(*eventCallback)(udpPacket);
	}
}

