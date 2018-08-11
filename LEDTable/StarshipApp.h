/*
 * StarshipApp.h
 *
 *  Created on: 23.10.2016
 *      Author: anonymous
 */

#ifndef STARSHIPAPP_H_
#define STARSHIPAPP_H_

#include <Arduino.h>
#include "App.h"
#include "LEDMatrix.h"

class Starship;

class StarshipApp: public App {
public:
	StarshipApp(LEDMatrix* pLEDMatrix);
	virtual ~StarshipApp();

	virtual void start();
	virtual void stop();
	virtual void run();

	void reset();

	inline uint8_t getPlayfield(uint8_t x, uint8_t y) {
		return playfield[x][y];
	}

	inline void setPlayfield(uint8_t x, uint8_t y, uint8_t val) {
		playfield[x][y] = val;
	}

	virtual void onButtonPressed(uint8_t button, uint8_t buttonStates);

	void gameOver(uint8_t player);

private:
	void action();
	void update();
	void updatePlayers();

	unsigned long int startMillis;
	unsigned long int currentMillis;
	unsigned long int lastMillis;
	unsigned long int speed;

	uint8_t noPlayers;

	bool gameStarted;

	uint8_t playfield[12][12];

	static uint8_t palette[8][3];

	uint8_t player1X;
	uint8_t player1Y;

	uint8_t player2X;
	uint8_t player2Y;

	struct Android {
		uint8_t x;
		uint8_t y;
		uint8_t type;
		unsigned long int speed;
		unsigned long int lastMoved;
		Android* pNext;
	};

	Android firstAndroid;
	uint8_t noOfAndroids;
};

#endif /* STARSHIPAPP_H_ */
