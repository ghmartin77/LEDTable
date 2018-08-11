/*
 * DMXRendererApp.h
 *
 *  Created on: 23.07.2016
 *      Author: anonymous
 */

#ifndef DMXRENDERERAPP_H_
#define DMXRENDERERAPP_H_

#include "App.h"
#include "LEDMatrix.h"
#include "ArtnetWifi.h"

class DMXRendererApp: public App {
public:
	DMXRendererApp(LEDMatrix* pLEDMatrix);
	virtual ~DMXRendererApp();

	virtual void start();
	virtual void stop();
	virtual void run();

	virtual void onButtonPressed(uint8_t button, uint8_t buttonStates);

private:
	ArtnetWifi artnet;

	static LEDMatrix* pLEDMATRIX;
	static void onDmxFrame(uint16_t universe, uint16_t length, uint8_t sequence,
			uint8_t* data);

	float calR = 1.0f;
	float calG = 1.0f;
	float calB = 1.0f;
};

#endif /* DMXRENDERERAPP_H_ */
