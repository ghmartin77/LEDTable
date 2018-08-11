/*
 * SnakeApp.cpp
 *
 *  Created on: 30.07.2016
 *      Author: anonymous
 */

#include "SnakeApp.h"

uint8_t SnakeApp::palette[][3] = { { 0, 0, 0 }, { 255, 255, 255 },
		{ 255, 0, 0 }, { 100, 0, 0 }, { 0, 0, 255 }, { 0, 0, 100 } };

SnakeApp::SnakeApp(LEDMatrix* pLEDMatrix) :
		App(pLEDMatrix), lastMillis(0), speed(400), gameStarted(false), noPlayers(
				1), spawnNewPill(true) {
	name = "Snake";
	snake1 = new Snake(this, 1);
	snake2 = new Snake(this, 2);
}

SnakeApp::~SnakeApp() {
	delete snake1;
	delete snake2;
}

void SnakeApp::start() {
	reset();
	randomSeed(micros());
}

void SnakeApp::reset() {
	gameStarted = false;
	noPlayers = 1;
	pMatrix->clear();
	for (int x = 0; x < 12; ++x) {
		for (int y = 0; y < 12; ++y) {
			playfield[x][y] = 0;
		}
	}
	snake1->reset();
	snake2->reset();

	lastMillis = millis();
	snake1->action1();
	snake1->action2();
	spawnNewPill = true;
	update();
}

void SnakeApp::run() {
	unsigned long int currentMillis = millis();

	if (gameStarted) {
		if (currentMillis - speed < lastMillis) {
			return;
		}

		lastMillis = currentMillis;

		action();
		update();
	} else {
		gameStarted = currentMillis - 5000 >= lastMillis;
	}
}

void SnakeApp::action() {
	snake1->action1();
	if (noPlayers == 2) {
		snake2->action1();
	}

	spawnNewPill |= snake1->action2();
	if (noPlayers == 2) {
		spawnNewPill |= snake2->action2();
	}

	if (spawnNewPill && random(6) == 0) {

		bool foundValidPos = false;
		while (!foundValidPos) {
			uint8_t x = random(12);
			uint8_t y = random(12);

			if (playfield[x][y] == 0) {
				playfield[x][y] = 1;
				spawnNewPill = false;
				foundValidPos = true;
			}
		}
	}
}

void SnakeApp::update() {
	for (int x = 0; x < 12; ++x)
		for (int y = 0; y < 12; ++y) {
			pMatrix->setPixel(x, y, palette[playfield[x][y]][0],
					palette[playfield[x][y]][1], palette[playfield[x][y]][2]);
		}

	pMatrix->update();
}

void SnakeApp::onButtonPressed(uint8_t button, uint8_t buttonStates) {
	if (gameStarted) {
		switch (button) {
		case 1:
			snake1->moveLeft();
			break;
		case 2:
			snake1->moveRight();
			break;
		case 3:
			snake2->moveLeft();
			break;
		case 4:
			snake2->moveRight();
			break;
		}
	} else {
		unsigned long int currentMillis = millis();

		if (currentMillis - lastMillis > 500) {
			if (button == 1 || button == 2) {
				lastMillis = 0;
			} else if ((button == 3 || button == 4) && noPlayers != 2) {
				noPlayers = 2;
				snake2->action1();
				snake2->action2();
				update();
				lastMillis = currentMillis - 4000;
			}
		}
	}
}

void SnakeApp::gameOver(uint8_t snake) {
	snake = snake * 2;
	pMatrix->fill(palette[snake][0], palette[snake][1], palette[snake][2]);
	delay(3000);
	reset();
}
