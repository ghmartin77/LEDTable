/*
 * PongApp.cpp
 *
 *  Created on: 23.10.2016
 *      Author: anonymous
 */

#include "PongApp.h"

uint8_t PongApp::palette[][3] = { { 0, 0, 0 }, { 255, 255, 255 }, { 255, 0, 0 },
		{ 100, 0, 0 }, { 0, 0, 255 }, { 0, 0, 100 } };

PongApp::PongApp(LEDMatrix* pLEDMatrix) :
		App(pLEDMatrix), startMillis(0), lastMillis(0), currentMillis(0), speed(
				40), gameStarted(
		false), noPlayers(1) {
	name = "Pong";
	player1X = 0;
	player1Y = 4;
	player2X = 11;
	player2Y = 4;

	ballX = 5;
	ballY = 5;

	ballDirectionX = random(100) < 50 ? 1 : -1;
	ballDirectionY = random(100) < 50 ? 1 : -1;
	ballSpeed = 400;
	ballLastMillisMoved = 0;
}

PongApp::~PongApp() {
}

void PongApp::start() {
	reset();
	randomSeed((unsigned long int) micros());
}

void PongApp::stop() {
}

void PongApp::reset() {
	gameStarted = false;
	noPlayers = 2;
	pMatrix->clear();
	player1Y = player2Y = 4;

	ballX = 5 + (random(100) < 50 ? 1 : 0);
	ballY = 5 + (random(100) < 50 ? 1 : 0);

	ballDirectionX = random(100) < 50 ? 1 : -1;
	ballDirectionY = random(100) < 50 ? 1 : -1;
	ballSpeed = 400;

	lastMillis = millis();
	startMillis = lastMillis;
	ballLastMillisMoved = lastMillis - ballSpeed;

	update();
}

void PongApp::run() {
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
		ballLastMillisMoved = currentMillis - ballSpeed;
	}
}

void PongApp::action() {
	if (currentMillis - ballLastMillisMoved >= ballSpeed) {
		moveBall();
	}
}

void PongApp::moveBall() {
//	ballLastMillisMoved = currentMillis
//			- (currentMillis - ballLastMillisMoved - ballSpeed);
	ballLastMillisMoved = currentMillis;

	pMatrix->setPixel(ballX, ballY, palette[0][0], palette[0][1],
			palette[0][2]);

	if (ballX >= 11 || ballX <= 0) {
		ballDirectionX = -ballDirectionX;
		gameOver(ballX == 0 ? 1 : 2);
		return;
	}
	if ((ballY >= 11 && ballDirectionY == 1)
			|| (ballY <= 0 && ballDirectionY == -1)) {
		ballDirectionY = -ballDirectionY;
	}

	ballX += ballDirectionX;
	ballY += ballDirectionY;

	if (ballX == 0) {
		if (ballY >= player1Y && ballY <= player1Y + 3) {
			boolean reverseDirectionY = (ballY == player1Y
					&& ballDirectionY == 1)
					|| (ballY == player1Y + 3 && ballDirectionY == -1);
			ballX -= ballDirectionX;
			ballY -= ballDirectionY;
			ballDirectionX = -ballDirectionX;
			if (reverseDirectionY)
				ballDirectionY = -ballDirectionY;

			ballSpeed += (2 - random(7)) * 5;
			if (ballSpeed < 50) {
				ballSpeed = 50;
			}
			moveBall();
		}
	} else if (ballX == 11) {
		if (ballY >= player2Y && ballY <= player2Y + 3) {
			boolean reverseDirectionY = (ballY == player2Y
					&& ballDirectionY == 1)
					|| (ballY == player2Y + 3 && ballDirectionY == -1);
			ballX -= ballDirectionX;
			ballY -= ballDirectionY;
			ballDirectionX = -ballDirectionX;
			if (reverseDirectionY)
				ballDirectionY = -ballDirectionY;

			ballSpeed += (2 - random(7)) * 5;
			if (ballSpeed < 50) {
				ballSpeed = 50;
			}
			moveBall();
		}
	}

	pMatrix->setPixel(ballX, ballY, palette[1][0], palette[1][1],
			palette[1][2]);
}

void PongApp::updatePlayers() {
	for (int i = 0; i < 12; ++i) {
		pMatrix->setPixel(player1X, i, palette[0][0], palette[0][1],
				palette[0][2]);
		pMatrix->setPixel(player2X, i, palette[0][0], palette[0][1],
				palette[0][2]);
	}

	pMatrix->setPixel(player1X, player1Y, palette[2][0], palette[2][1],
			palette[2][2]);
	pMatrix->setPixel(player1X, player1Y + 1, palette[2][0], palette[2][1],
			palette[2][2]);
	pMatrix->setPixel(player1X, player1Y + 2, palette[2][0], palette[2][1],
			palette[2][2]);
	pMatrix->setPixel(player1X, player1Y + 3, palette[2][0], palette[2][1],
			palette[2][2]);

	pMatrix->setPixel(player2X, player2Y, palette[4][0], palette[4][1],
			palette[4][2]);
	pMatrix->setPixel(player2X, player2Y + 1, palette[4][0], palette[4][1],
			palette[4][2]);
	pMatrix->setPixel(player2X, player2Y + 2, palette[4][0], palette[4][1],
			palette[4][2]);
	pMatrix->setPixel(player2X, player2Y + 3, palette[4][0], palette[4][1],
			palette[4][2]);

	pMatrix->setPixel(ballX, ballY, palette[1][0], palette[1][1],
			palette[1][2]);
}

void PongApp::update() {
	updatePlayers();

	pMatrix->update();
}

void PongApp::onButtonPressed(uint8_t button, uint8_t buttonStates) {
	if (gameStarted) {
		switch (button) {
		case 1:
			if ((buttonStates & 2) == 0) {
				if (player1Y > 0 && (ballX != 0 || ballY != player1Y - 1))
					player1Y--;
			}
			break;
		case 2:
			if ((buttonStates & 1) == 0) {
				if (player1Y < 8 && (ballX != 0 || ballY != player1Y + 4))
					player1Y++;
			}
			break;
		case 3:
			if (noPlayers == 2 && (buttonStates & 8) == 0) {
				if (player2Y > 0 && (ballX != 11 || ballY != player2Y - 1))
					player2Y--;
			}
			break;
		case 4:
			if (noPlayers == 2 && (buttonStates & 4) == 0) {
				if (player2Y < 8 && (ballX != 11 || ballY != player2Y + 4))
					player2Y++;
			}
			break;
		}
	} else {
		unsigned long int currentMillis = millis();

		if (currentMillis - lastMillis > 500) {
			if (button == 1 || button == 2) {
				lastMillis = 0;
			} else if ((button == 3 || button == 4) && noPlayers != 2) {
				noPlayers = 2;
				update();
				lastMillis = currentMillis - 4000;
			}
		}
	}
}

void PongApp::gameOver(uint8_t player) {
	player = player * 2;
	pMatrix->fill(palette[player][0], palette[player][1], palette[player][2]);
	delay(3000);
	reset();
}
