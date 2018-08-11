/*
 * Snake.cpp
 *
 *  Created on: 30.07.2016
 *      Author: anonymous
 */

#include "Snake.h"
#include "SnakeApp.h"

Snake::Snake(SnakeApp* pApp, uint8_t aPlayer) :
		pSnakeApp(pApp), player(aPlayer) {
	reset();
}

Snake::~Snake() {
}

void Snake::action1() {
	if (growBy > 0) {
		growBy--;

		if (length < 60) {
			++length;
		}
	} else {
		uint8_t pos = positions[length - 1];
		pSnakeApp->setPlayfield(pos >> 4, pos & 15, 0);
	}
}

bool Snake::action2() {
	for (int i = length; i > 0; --i) {
		positions[i] = positions[i - 1];
	}

	uint8_t headX = positions[0] >> 4;
	uint8_t headY = positions[0] & 15;

	pSnakeApp->setPlayfield(headX, headY, player * 2 + 1);

	switch (direction) {
	case 0:
		if (headY == 0) {
			headY = 11;
		} else {
			headY--;
		}
		break;
	case 1:
		if (headX == 11) {
			headX = 0;
		} else {
			headX++;
		}
		break;
	case 2:
		if (headY == 11) {
			headY = 0;
		} else {
			headY++;
		}
		break;
	case 3:
		if (headX == 0) {
			headX = 11;
		} else {
			headX--;
		}
		break;
	}

	uint8_t headPiece = pSnakeApp->getPlayfield(headX, headY);

	positions[0] = headX << 4 | headY;
	pSnakeApp->setPlayfield(headX, headY, player * 2);

	movePossible = true;

	if (headPiece == 1) {
		growBy += 2;
		return true;
	} else if (headPiece != 0) {
		pSnakeApp->gameOver(player);
	}

	return false;
}

void Snake::moveLeft() {
	if (!movePossible)
		return;

	if (direction == 0) {
		direction = 3;
	} else {
		direction--;
	}
	movePossible = false;
}

void Snake::moveRight() {
	if (!movePossible)
		return;

	if (direction == 3) {
		direction = 0;
	} else {
		direction++;
	}
	movePossible = false;
}

void Snake::reset() {
	movePossible = true;
	length = 2;
	growBy = 0;

	if (player == 1) {
		direction = 1;
		positions[0] = 1 << 4 | 5;
		positions[1] = 2 << 4 | 5;
	} else if (player == 2) {
		direction = 3;
		positions[0] = 10 << 4 | 6;
		positions[1] = 11 << 4 | 6;
	}
}
