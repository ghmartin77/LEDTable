/*
 * TetrisApp.cpp
 *
 *  Created on: 23.07.2016
 *      Author: anonymous
 */

#include "TetrisApp.h"
#include "Shapes.h"

TetrisApp::TetrisApp(LEDMatrix* pLEDMatrix) :
		App(pLEDMatrix), lastMillis(0), speed(750) {
	name = "Tetris";
}

TetrisApp::~TetrisApp() {
}

void TetrisApp::start() {
	pMatrix->clear();

	pit.clear();
	randomSeed(micros());

	piece.spawn();

	lastMillis = millis();
	update();
}

void TetrisApp::run() {
	unsigned long int currentMillis = millis();

	if (currentMillis - speed < lastMillis) {
		return;
	}

	lastMillis = currentMillis;

	action();
	update();
}

void TetrisApp::action() {
	piece.action(0);
	if (!piece.fits(&pit)) {
		piece.action(1);
		piece.add(&pit);
		piece.spawn();
		if (!piece.fits(&pit)) {
			pit.clear();
		}
	}
}

void TetrisApp::update() {
	pit.draw(pMatrix);
	piece.draw(pMatrix);

	pMatrix->update();
}

void TetrisApp::onButtonPressed(uint8_t button, uint8_t buttonStates) {
	switch (button) {
	case 1:
		if ((buttonStates & 8) == 0) {
			piece.action(3);
			if (!piece.fits(&pit)) {
				piece.action(2);
			} else {
				update();
			}
		}
		break;
	case 2:
		piece.action(0);
		lastMillis = millis();
		if (!piece.fits(&pit)) {
			piece.action(1);
			action();
		} else {
			update();
		}
		break;
	case 3:
		piece.action(4);
		if (!piece.fits(&pit)) {
			piece.action(5);
		} else {
			update();
		}
		break;
	case 4:
		if ((buttonStates & 1) == 0) {
			piece.action(2);
			if (!piece.fits(&pit)) {
				piece.action(3);
			} else {
				update();
			}
		}
		break;
	}
}
