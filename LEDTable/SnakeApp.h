/*
 * SnakeApp.h
 *
 *  Created on: 30.07.2016
 *      Author: anonymous
 */

#ifndef SNAKEAPP_H_
#define SNAKEAPP_H_

#include <Arduino.h>
#include "App.h"
#include "LEDMatrix.h"
#include "Snake.h"

class Snake;

class SnakeApp: public App {
public:
	SnakeApp(LEDMatrix* pLEDMatrix);
	virtual ~SnakeApp();

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

	void gameOver(uint8_t snake);

private:
	void action();
	void update();

	unsigned long int lastMillis;
	unsigned long int speed;

	uint8_t noPlayers;

	bool gameStarted;
	bool spawnNewPill;

	uint8_t playfield[12][12];

	static uint8_t palette[8][3];

	Snake* snake1;
	Snake* snake2;
};

#endif /* SNAKEAPP_H_ */
