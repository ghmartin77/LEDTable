/*
 * Snake.h
 *
 *  Created on: 30.07.2016
 *      Author: anonymous
 */

#ifndef SNAKE_H_
#define SNAKE_H_

#include <Arduino.h>

class SnakeApp;

class Snake {
public:
	Snake(SnakeApp* pApp, uint8_t aPlayer);
	virtual ~Snake();

	void action1();
	bool action2();
	void reset();

	void moveLeft();
	void moveRight();

private:
	uint8_t player;
	bool movePossible;
	uint8_t direction;
	uint8_t length;
	uint8_t growBy;
	uint8_t positions[64];

	SnakeApp* pSnakeApp;
};

#endif /* SNAKE_H_ */
