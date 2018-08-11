/*
 * TetrisApp.h
 *
 *  Created on: 23.07.2016
 *      Author: anonymous
 */

#ifndef TETRISAPP_H_
#define TETRISAPP_H_

#include "App.h"
#include "LEDMatrix.h"
#include "Pit.h"
#include "Piece.h"

class TetrisApp: public App {
public:
	TetrisApp(LEDMatrix* pLEDMatrix);
	virtual ~TetrisApp();

	virtual void start();
	virtual void run();

	virtual void onButtonPressed(uint8_t button, uint8_t buttonStates);

private:
	void action();
	void update();

	unsigned long int lastMillis;
	unsigned long int speed;
	Pit pit;
	Piece piece;

};

#endif /* TETRISAPP_H_ */
