/*
 * VisualizerApp.h
 *
 *  Created on: 21.08.2016
 *      Author: anonymous
 */

#ifndef VISUALIZERAPP_H_
#define VISUALIZERAPP_H_

#include "App.h"
#include "Visualizer.h"

class VisualizerApp: public App {
public:
	VisualizerApp(LEDMatrix* pLEDMatrix);
	virtual ~VisualizerApp();

	virtual void start();
	virtual void run();
	virtual void stop();

	virtual void onButtonPressed(uint8_t button, uint8_t buttonStates);

	void setVisualizer(uint8_t idx, Visualizer* pVisualizer);

private:
	Visualizer* visualizers[4] = { NULL, NULL, NULL, NULL };
	unsigned long int lastMillis;
};

#endif /* VISUALIZERAPP_H_ */
