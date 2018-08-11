/*
 * PongApp.h
 *
 *  Created on: 23.10.2016
 *      Author: anonymous
 */

#ifndef PONGAPP_H_
#define PONGAPP_H_

#include <Arduino.h>
#include "App.h"
#include "LEDMatrix.h"

class Pong;

class PongApp: public App {
public:
	PongApp(LEDMatrix* pLEDMatrix);
	virtual ~PongApp();

	virtual void start();
	virtual void stop();
	virtual void run();

	void reset();

	void moveBall();

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

	static uint8_t palette[8][3];

	uint8_t player1X;
	uint8_t player1Y;

	uint8_t player2X;
	uint8_t player2Y;

	int8_t ballX;
	int8_t ballY;
	int8_t ballDirectionX;
	int8_t ballDirectionY;
	uint16_t ballSpeed;
	unsigned long int ballLastMillisMoved;
};

#endif /* PONGAPP_H_ */
