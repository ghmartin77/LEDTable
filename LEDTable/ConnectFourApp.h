/*
 * FourWinsApp.h
 *
 *  Created on: 28.07.2016
 *      Author: anonymous
 */

#ifndef CONNECTFOURAPP_H_
#define CONNECTFOURAPP_H_

#include "App.h"
#include "LEDMatrix.h"

class ConnectFourApp: public App {
public:
	ConnectFourApp(LEDMatrix* pLEDMatrix);
	virtual ~ConnectFourApp();

	virtual void start();
	virtual void run();
	void reset();

	inline uint8_t getPlayfield(uint8_t x, uint8_t y) {
		return playfield[x][y];
	}

	inline void setPlayfield(uint8_t x, uint8_t y, uint8_t val) {
		playfield[x][y] = val;
	}

	virtual void onButtonPressed(uint8_t button, uint8_t buttonStates);

protected:
	bool checkWon();

private:
	void action();
	void update();

	unsigned long int lastMillis;

	bool pieceFalling;
	bool gameWon;

	uint8_t activePlayer;
	uint8_t playerX;
	uint8_t playerY;

	uint8_t playfield[12][12];

	static uint8_t palette[6][3];
};

#endif /* CONNECTFOURAPP_H_ */
