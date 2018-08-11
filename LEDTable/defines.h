/*
 * defines.h
 *
 *  Created on: 21.07.2016
 *      Author: anonymous
 */

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <WiFiClient.h>

#ifndef DEFINES_H_
#define DEFINES_H_

#define WIFI_SSID     "xxxxxxxxxxxxxxxx"
#define WIFI_PASSWORD "xxxxxxxxxxxxxxxx"

#define UDP_PORT 6789

#define BUTTON_SAMPLES 3
#define BUTTON_THRESHOLD 80

#define BUTTON_REPEAT_DELAY 150

#ifdef DEBUG
extern WiFiClient serverClient;

inline void TCPLOG(const char* pC) {
	if (serverClient && serverClient.connected())
		serverClient.write(pC);
}
#endif

#endif /* DEFINES_H_ */
