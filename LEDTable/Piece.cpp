/*
 * Piece.cpp
 *
 *  Created on: 24.07.2016
 *      Author: anonymous
 */

#include "Piece.h"
#include "Shapes.h"

#define deltaX (-2)
#define deltaY (-1)

Piece::Piece() :
		orientation(0), shape(0), posX(0), posY(0) {
}

Piece::~Piece() {
}

void Piece::spawn() {
	shape = random(7);
	posX = 5;
	posY = 0;
	orientation = 0;
}

void Piece::action(uint8_t act) {
	switch (act) {
	case 0:
		posY++;
		break;
	case 1:
		posY--;
		break;
	case 2:
		posX++;
		break;
	case 3:
		posX--;
		break;
	case 4:
		orientation++;
		if (orientation > 3)
			orientation = 0;
		break;
	case 5:
		orientation--;
		if (orientation < 0)
			orientation = 3;
		break;
	}
}

void Piece::draw(LEDMatrix* pMatrix) {
	for (int x = 0; x < 4; ++x)
		for (int y = 0; y < 4; ++y) {
			if (shapes[shape][orientation][y][x] > 0) {
				int8_t realX = x + posX + deltaX + 1;
				int8_t realY = y + posY + deltaY;

				pMatrix->setPixel(realX, realY,
						shapeColors[shapes[shape][orientation][y][x]][0],
						shapeColors[shapes[shape][orientation][y][x]][1],
						shapeColors[shapes[shape][orientation][y][x]][2]);
			}
		}
}

void Piece::clear(LEDMatrix* pMatrix) {
	for (int x = 0; x < 4; ++x)
		for (int y = 0; y < 4; ++y) {
			if (shapes[shape][orientation][y][x] > 0) {
				int8_t realX = x + posX + deltaX + 1;
				int8_t realY = y + posY + deltaY;

				pMatrix->setPixel(realX, realY, 0, 0, 0);
			}
		}
}

bool Piece::fits(Pit* pPit) {
	for (int x = 0; x < 4; ++x)
		for (int y = 0; y < 4; ++y) {
			if (shapes[shape][orientation][y][x] > 0) {
				int8_t realX = x + posX + deltaX;
				int8_t realY = y + posY + deltaY;

				if (realY >= 0
						&& (realY > 11 || realX < 0 || realX > 9
								|| pPit->get(realX, realY) > 0))
					return false;
			}
		}

	return true;
}

void Piece::add(Pit *pPit) {
	for (int x = 0; x < 4; ++x)
		for (int y = 0; y < 4; ++y) {
			if (shapes[shape][orientation][y][x] > 0) {
				int8_t realX = x + posX + deltaX;
				int8_t realY = y + posY + deltaY;

				pPit->set(realX, realY, shapes[shape][orientation][y][x]);
			}
		}
	pPit->rollUp();
}

