/*
 * StarshipApp.cpp
 *
 *  Created on: 23.10.2016
 *      Author: anonymous
 */

#include "StarshipApp.h"

uint8_t StarshipApp::palette[][3] = { { 0, 0, 0 }, { 255, 255, 255 }, { 255, 0,
		0 }, { 100, 0, 0 }, { 0, 0, 255 }, { 0, 0, 100 } };

StarshipApp::StarshipApp(LEDMatrix* pLEDMatrix) :
		App(pLEDMatrix), startMillis(0), lastMillis(0), currentMillis(0), speed(
				20), gameStarted(
		false), noPlayers(1) {
	name = "Starship";
	player1X = 6;
	player1Y = 10;
	player2X = 5;
	player2Y = 11;
	noOfAndroids = 0;
	firstAndroid.pNext = NULL;
}

StarshipApp::~StarshipApp() {
}

void StarshipApp::start() {
	reset();
	randomSeed(micros());
}

void StarshipApp::stop() {
	Android* pA = firstAndroid.pNext;

	while (pA != NULL) {
		Android* pNextA = pA->pNext;
		delete pA;
		pA = pNextA;
	}

	firstAndroid.pNext = NULL;
}

void StarshipApp::reset() {
	Android* pA = firstAndroid.pNext;

	while (pA != NULL) {
		Android* pNextA = pA->pNext;
		delete pA;
		pA = pNextA;
	}
	noOfAndroids = 0;
	firstAndroid.pNext = NULL;

	gameStarted = false;
	noPlayers = 1;
	pMatrix->clear();
	for (int x = 0; x < 12; ++x) {
		for (int y = 0; y < 12; ++y) {
			playfield[x][y] = 0;
		}
	}
	player1X = 6;
	player2X = 5;

	lastMillis = millis();
	startMillis = lastMillis;
	update();
}

void StarshipApp::run() {
	currentMillis = millis();

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

void StarshipApp::action() {
	if (noOfAndroids < ((currentMillis - startMillis) / 10000) + 2) {
		Android* pA = new Android();
		pA->type = 1;
		pA->x = random(12);
		pA->y = 0;
		pA->speed = 200 + random(800);
		pA->lastMoved = currentMillis + pA->speed;
		pA->pNext = firstAndroid.pNext;
		firstAndroid.pNext = pA;

		noOfAndroids++;
	}

	Android *pAndroid2Delete = NULL;
	Android* pA = firstAndroid.pNext;
	while (pA != NULL) {

		unsigned long int nextMoveAt = pA->lastMoved + pA->speed;
		if (nextMoveAt < currentMillis) {
			pA->y++;
			pA->lastMoved = nextMoveAt;

			if (pA->y >= 12) {
				pAndroid2Delete = pA;
				Android* pA2 = &firstAndroid;
				while (pA2) {
					if (pA2->pNext == pA) {
						pA2->pNext = pA->pNext;
						pA2 == NULL;
					} else {
						pA2 = pA2->pNext;
					}
				}
			}
		}

		pA = pA->pNext;

		if (pAndroid2Delete) {
			delete pAndroid2Delete;
			pAndroid2Delete = NULL;

			noOfAndroids--;
		}
	}
}

void StarshipApp::updatePlayers() {
	if (pMatrix->getPixel(player1X, player1Y) == 0) {
		pMatrix->setPixel(player1X, player1Y, palette[2][0], palette[2][1],
				palette[2][2]);
	} else {
		gameOver(1);
	}

	if (noPlayers == 2) {
		if (pMatrix->getPixel(player2X, player2Y) == 0) {
			pMatrix->setPixel(player2X, player2Y, palette[4][0], palette[4][1],
					palette[4][2]);
		} else {
			gameOver(2);
		}
	}
}

void StarshipApp::update() {
	// clear playfield
	pMatrix->clear(false);

	// render androids
	Android* pA = firstAndroid.pNext;
	while (pA != NULL) {
		pMatrix->setPixel(pA->x, pA->y, palette[1][0], palette[1][1],
				palette[1][2]);

		pA = pA->pNext;
	}

	updatePlayers();

	pMatrix->update();
}

void StarshipApp::onButtonPressed(uint8_t button, uint8_t buttonStates) {
	if (gameStarted) {
		switch (button) {
		case 1:
			if ((buttonStates & 2) == 0) {
				pMatrix->setPixel(player1X, player1Y, 0, 0, 0);
				if (noPlayers == 2)
					pMatrix->setPixel(player2X, player2Y, 0, 0, 0);
				if (player1X > 0)
					player1X--;
			}
			break;
		case 2:
			if ((buttonStates & 1) == 0) {
				pMatrix->setPixel(player1X, player1Y, 0, 0, 0);
				if (noPlayers == 2)
					pMatrix->setPixel(player2X, player2Y, 0, 0, 0);
				if (player1X < 11)
					player1X++;
			}
			break;
		case 3:
			if (noPlayers == 2 && (buttonStates & 8) == 0) {
				pMatrix->setPixel(player1X, player1Y, 0, 0, 0);
				pMatrix->setPixel(player2X, player2Y, 0, 0, 0);
				if (player2X > 0)
					player2X--;
			}
			break;
		case 4:
			if (noPlayers == 2) {
				if ((buttonStates & 4) == 0) {
					pMatrix->setPixel(player1X, player1Y, 0, 0, 0);
					pMatrix->setPixel(player2X, player2Y, 0, 0, 0);
					if (player2X < 11)
						player2X++;
				}
			} else {
				if ((buttonStates & 1) == 0) {
					pMatrix->setPixel(player1X, player1Y, 0, 0, 0);
					if (player1X < 11)
						player1X++;
				}
				break;
			}
			break;
		}
	} else {
		unsigned long int currentMillis = millis();

		if (currentMillis - lastMillis > 500) {
			if (button == 1 || button == 2) {
				lastMillis = 0;
			} else if (button == 3 && noPlayers != 2) {
				noPlayers = 2;
				update();
				lastMillis = currentMillis - 4000;
			}
		}
	}
}

void StarshipApp::gameOver(uint8_t player) {
	player = player * 2;
	pMatrix->fill(palette[player][0], palette[player][1], palette[player][2]);
	delay(3000);
	reset();
}
