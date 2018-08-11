/*
 * Piece.h
 *
 *  Created on: 24.07.2016
 *      Author: anonymous
 */

#ifndef PIECE_H_
#define PIECE_H_

#include "Pit.h"
#include "LEDMatrix.h"

class Piece {
public:
	Piece();
	virtual ~Piece();

	void spawn();

	void draw(LEDMatrix *pMatrix);
	void clear(LEDMatrix *pMatrix);

	void action(uint8_t act);

	bool fits(Pit* pPit);
	void add(Pit* pPit);

private:
	int8_t orientation;
	uint8_t shape;
	uint8_t posX;
	uint8_t posY;
};

#endif /* PIECE_H_ */
