/*
 * FadeAndScrollVisualizer.h
 *
 *  Created on: 22.08.2016
 *      Author: anonymous
 */

#ifndef FADEANDSCROLLVISUALIZER_H_
#define FADEANDSCROLLVISUALIZER_H_

#include "Visualizer.h"

class FadeAndScrollVisualizer: public Visualizer {
public:
	FadeAndScrollVisualizer(uint8_t _fsSpeed, uint8_t _fsZoom);
	virtual ~FadeAndScrollVisualizer();

	virtual void start();
	virtual void stop();

	virtual void onButtonPressed(uint8_t button, uint8_t buttonStates);

protected:
	virtual void computeImage();

private:
	uint8_t mode;
	int8_t direction;
	int8_t fsSpeed;
	int16_t fsZoom;
	uint16_t fsIndex;
	int16_t* pFsHeight;
	uint8_t* pFsLut;

	void updateFsHeight();
};

#endif /* FADEANDSCROLLVISUALIZER_H_ */
