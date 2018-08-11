/*
 * FourWinsApp.cpp
 *
 *  Created on: 28.07.2016
 *      Author: anonymous
 */

#include "ConnectFourApp.h"

uint8_t ConnectFourApp::palette[][3] = { { 0, 0, 0 }, { 255, 0, 0 },
		{ 0, 0, 255 }, { 255, 255, 255 }, { 16, 0, 0 }, { 0, 0, 16 } };

ConnectFourApp::ConnectFourApp(LEDMatrix* pLEDMatrix) :
		App(pLEDMatrix), lastMillis(0), activePlayer(0), playerX(5), playerY(0), pieceFalling(
		false), gameWon(false) {
	name = "Connect Four";
}

ConnectFourApp::~ConnectFourApp() {

}

void ConnectFourApp::start() {
	reset();
}

void ConnectFourApp::reset() {
	gameWon = false;
	pieceFalling = false;
	activePlayer = 0;
	playerX = 5;
	playerY = 0;
	lastMillis = 0;

	for (int x = 0; x < 12; ++x) {
		for (int y = 0; y < 12; ++y) {
			playfield[x][y] = 0;
		}
	}

	lastMillis = millis();

	update();
}

void ConnectFourApp::run() {
	unsigned long int currentMillis = millis();

	if (!pieceFalling || gameWon) {
		if (currentMillis - 40 < lastMillis) {
			return;
		}
		lastMillis = currentMillis;
		update();
	} else {
		if (currentMillis - 50 < lastMillis) {
			return;
		}

		lastMillis = currentMillis;

		if (playerY < 11 && playfield[playerX][playerY + 1] == 0) {
			playerY++;
		} else {
			playfield[playerX][playerY] = activePlayer + 1;

			if (!checkWon()) {
				if (++activePlayer > 1)
					activePlayer = 0;

				playerX = 5;
				playerY = 0;
			}
			pieceFalling = false;
		}
		update();
	}
}

void ConnectFourApp::update() {
	for (int x = 0; x < 12; ++x)
		for (int y = 0; y < 12; ++y) {
			pMatrix->setPixel(x, y, palette[playfield[x][y]][0],
					palette[playfield[x][y]][1], palette[playfield[x][y]][2]);
		}

	if (!gameWon) {
		pMatrix->setPixel(playerX, playerY, palette[activePlayer + 1][0],
				palette[activePlayer + 1][1], palette[activePlayer + 1][2]);

		// preview
		if (!pieceFalling) {
			int y = 0;
			while (y < 11 && playfield[playerX][y + 1] == 0)
				++y;

			if (y > 0)
				pMatrix->setPixel(playerX, y, palette[activePlayer + 4][0],
						palette[activePlayer + 4][1],
						palette[activePlayer + 4][2]);
		}
	}

	pMatrix->update();
}

void ConnectFourApp::onButtonPressed(uint8_t button, uint8_t buttonStates) {
	if (gameWon) {
		reset();
		return;
	}

	if (pieceFalling)
		return;

	switch (button) {
	case 1:
		if ((buttonStates & 8) == 0) {
			if (playerX > 0) {
				playerX--;
			}
		}
		break;
	case 2:
	case 3:
		if (playfield[playerX][playerY + 1] == 0) {
			pieceFalling = true;
		}
		break;
	case 4:
		if ((buttonStates & 1) == 0) {
			if (playerX < 11) {
				playerX++;
			}
		}
		break;
	}
}

/*
 * Naive implementation, checks way too many situations
 */
bool ConnectFourApp::checkWon() {
	int8_t val = activePlayer + 1;

	for (int x = 0; x < 12; ++x) {
		for (int y = 1; y < 12; ++y) {
			if (x < 9 && playfield[x][y] == val && playfield[x + 1][y] == val
					&& playfield[x + 2][y] == val
					&& playfield[x + 3][y] == val) {
				playfield[x][y] = playfield[x + 1][y] = playfield[x + 2][y] =
						playfield[x + 3][y] = 3;
				gameWon = true;
				update();
				return gameWon;
			}
			if (y < 9 && playfield[x][y] == val && playfield[x][y + 1] == val
					&& playfield[x][y + 2] == val
					&& playfield[x][y + 3] == val) {
				playfield[x][y] = playfield[x][y + 1] = playfield[x][y + 2] =
						playfield[x][y + 3] = 3;
				gameWon = true;
				update();
				return gameWon;
			}
			if (y < 9 && x < 9 && playfield[x][y] == val
					&& playfield[x + 1][y + 1] == val
					&& playfield[x + 2][y + 2] == val
					&& playfield[x + 3][y + 3] == val) {
				playfield[x][y] = playfield[x + 1][y + 1] = playfield[x + 2][y
						+ 2] = playfield[x + 3][y + 3] = 3;
				gameWon = true;
				update();
				return gameWon;
			}
			if (y > 3 && x < 9 && playfield[x][y] == val
					&& playfield[x + 1][y - 1] == val
					&& playfield[x + 2][y - 2] == val
					&& playfield[x + 3][y - 3] == val) {
				playfield[x][y] = playfield[x + 1][y - 1] = playfield[x + 2][y
						- 2] = playfield[x + 3][y - 3] = 3;
				gameWon = true;
				update();
				return gameWon;
			}
		}
	}

	return false;
}
