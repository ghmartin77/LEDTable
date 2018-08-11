/*
 * FallingObjectsVisualizer.h
 *
 *  Created on: 27.08.2016
 *      Author: anonymous
 */

#ifndef FALLINGOBJECTSVISUALIZER_H_
#define FALLINGOBJECTSVISUALIZER_H_

#include "Visualizer.h"

class FallingObjectsVisualizer: public Visualizer {
public:
	FallingObjectsVisualizer(uint8_t direction);
	virtual ~FallingObjectsVisualizer();

	virtual void start();
	virtual void stop();

	virtual void onButtonPressed(uint8_t button, uint8_t buttonStates);

protected:
	virtual void computeImage();

	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();

private:
	boolean foIsActive[12];
	uint8_t foPosition[12];
	uint8_t foRedValue = 0;
	uint8_t foGreenValue = 255;
	uint8_t foBlueValue = 255;
	uint8_t foLength = 20;
	uint8_t foNumber = 1;
	boolean foRandomColor = true;
	uint8_t foDirection = 0;
	uint8_t foRandomIntervall = 50;
	uint8_t foCounter = 0;
};

#endif /* FALLINGOBJECTSVISUALIZER_H_ */
