/*
 * VisualizerApp.cpp
 *
 *  Created on: 21.08.2016
 *      Author: anonymous
 */

#include "VisualizerApp.h"
#include "FadeAndScrollVisualizer.h"
#include "FallingObjectsVisualizer.h"

VisualizerApp::VisualizerApp(LEDMatrix* pLEDMatrix) :
		App(pLEDMatrix), lastMillis(0) {
	name = "Visualizer";

/*
	visualizers[0] = new FadeAndScrollVisualizer(10, 30);
	visualizers[0] = new FallingObjectsVisualizer(0);
	visualizers[1] = new FallingObjectsVisualizer(1);
	visualizers[2] = new FallingObjectsVisualizer(2);
	visualizers[3] = new FallingObjectsVisualizer(3);
*/
}

VisualizerApp::~VisualizerApp() {
}

void VisualizerApp::setVisualizer(uint8_t idx, Visualizer* pVisualizer) {
	visualizers[idx] = pVisualizer;
}


void VisualizerApp::start() {
	pMatrix->clear();

	for (int i = 0; i < 4; ++i) {
		if (visualizers[i]) {
			visualizers[i]->start();
		}
	}
}

void VisualizerApp::stop() {
	for (int i = 0; i < 4; ++i) {
		if (visualizers[i]) {
			visualizers[i]->stop();
		}
	}
}

void VisualizerApp::onButtonPressed(uint8_t button, uint8_t buttonStates) {
	for (int i = 0; i < 4; ++i) {
		if (visualizers[i]) {
			visualizers[i]->onButtonPressed(button, buttonStates);
		}
	}
}

void VisualizerApp::run() {
	unsigned long int currentMillis = millis();

	// run with 25 fps
	if (currentMillis - 40 < lastMillis) {
		return;
	}

	lastMillis = currentMillis;

	uint8_t* pImageData[4];

	for (int i = 0; i < 4; ++i) {
		if (visualizers[i]) {
			pImageData[i] = visualizers[i]->renderNextImage();
		} else {
			pImageData[i] = NULL;
		}
	}

	for (int i = 0; i < 12 * 12; ++i) {
		uint16_t r = 0, g = 0, b = 0;

		for (int j = 0; j < 4; ++j) {
			if (pImageData[j]) {
				r += pImageData[j][i * 3];
				if (r > 255)
					r = 255;
				g += pImageData[j][i * 3 + 1];
				if (g > 255)
					g = 255;
				b += pImageData[j][i * 3 + 2];
				if (b > 255)
					b = 255;
			}
		}

		pMatrix->setPixel(i % 12, i / 12, (uint8_t) r, (uint8_t) g,
				(uint8_t) b);
	}
	pMatrix->update();
}
