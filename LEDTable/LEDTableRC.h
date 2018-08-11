/*
 * LEDTableRC.h
 *
 *  Created on: 24.07.2016
 *      Author: anonymous
 */

#ifndef LEDTABLERC_H_
#define LEDTABLERC_H_

#include <WiFiUdp.h>

#include "defines.h"

#define MAX_BUFFER_RC 1024

class LEDTableRC {
public:
	LEDTableRC();
	virtual ~LEDTableRC();

	void begin();
	void update();
	inline void setEventCallback(void (*fptr)(uint8_t* eventData)) {
		eventCallback = fptr;
	}

private:
	uint8_t udpPacket[MAX_BUFFER_RC];
	WiFiUDP udp;

	void (*eventCallback)(uint8_t* data);

};

#endif /* LEDTABLERC_H_ */
