/*
 * FadeAndScrollVisualizer.cpp
 *
 *  Created on: 22.08.2016
 *      Author: anonymous
 */

#include "FadeAndScrollVisualizer.h"

FadeAndScrollVisualizer::FadeAndScrollVisualizer(uint8_t _fsSpeed,
		uint8_t _fsZoom) :
		fsSpeed(_fsSpeed), fsZoom(_fsZoom), pFsHeight(NULL), pFsLut(NULL), fsIndex(
				0), mode(0), direction(1) {
}

FadeAndScrollVisualizer::~FadeAndScrollVisualizer() {
}

void FadeAndScrollVisualizer::computeImage() {
	if (mode == 1) {
		for (int x = 0; x < 6; x++) {
			for (int y = 0; y < 6; y++) {
				fsIndex = y * 12 + x;
				pFsHeight[fsIndex] += fsSpeed * direction;
				if (pFsHeight[fsIndex] >= 1536) {
					pFsHeight[fsIndex] = pFsHeight[fsIndex] - 1536;
				} else if (pFsHeight[fsIndex] < 0) {
					pFsHeight[fsIndex] = pFsHeight[fsIndex] + 1536;
				}
				imageData[((11 - y) * 12 + 5 - x) * 3 + 0] = imageData[((11 - y)
						* 12 + 6 + x) * 3 + 0] = imageData[(y * 12 + 6 + x) * 3
						+ 0] = imageData[(y * 12 + 5 - x) * 3 + 0] =
						pFsLut[pFsHeight[fsIndex] * 3 + 0];

				imageData[((11 - y) * 12 + 5 - x) * 3 + 1] = imageData[((11 - y)
						* 12 + 6 + x) * 3 + 1] = imageData[(y * 12 + 6 + x) * 3
						+ 1] = imageData[(y * 12 + 5 - x) * 3 + 1] =
						pFsLut[pFsHeight[fsIndex] * 3 + 1];

				imageData[((11 - y) * 12 + 5 - x) * 3 + 2] = imageData[((11 - y)
						* 12 + 6 + x) * 3 + 2] = imageData[(y * 12 + 6 + x) * 3
						+ 2] = imageData[(y * 12 + 5 - x) * 3 + 2] =
						pFsLut[pFsHeight[fsIndex] * 3 + 2];

			}
		}
	} else {
		for (int x = 0; x < 12; x++) {
			for (int y = 0; y < 12; y++) {
				fsIndex = y * 12 + x;
				pFsHeight[fsIndex] += fsSpeed * direction;
				if (pFsHeight[fsIndex] >= 1536) {
					pFsHeight[fsIndex] = pFsHeight[fsIndex] - 1536;
				} else if (pFsHeight[fsIndex] < 0) {
					pFsHeight[fsIndex] = pFsHeight[fsIndex] + 1536;
				}
				imageData[fsIndex * 3 + 0] = pFsLut[pFsHeight[fsIndex] * 3 + 0];
				imageData[fsIndex * 3 + 1] = pFsLut[pFsHeight[fsIndex] * 3 + 1];
				imageData[fsIndex * 3 + 2] = pFsLut[pFsHeight[fsIndex] * 3 + 2];
			}
		}
	}
}

void FadeAndScrollVisualizer::updateFsHeight() {
	for (int x = 0; x < 12; x++) {
		for (int y = 0; y < 12; y++) {
			fsIndex = (y * 12 + x);
			pFsHeight[fsIndex] = ((x + 12 - y) * fsZoom % 1536);
		}
	}
}

void FadeAndScrollVisualizer::start() {
	fsIndex = 0;

	pFsLut = (uint8_t*) malloc(sizeof(uint8_t) * 3 * 1536);
	pFsHeight = (int16_t*) malloc(sizeof(int16_t) * 12 * 12);

	for (int i = 0; i < 256; ++i) {
		pFsLut[(i + 0) * 3 + 0] = 255;
		pFsLut[(i + 0) * 3 + 1] = i;
		pFsLut[(i + 0) * 3 + 2] = 0;

		pFsLut[(i + 256) * 3 + 0] = 255 - i;
		pFsLut[(i + 256) * 3 + 1] = 255;
		pFsLut[(i + 256) * 3 + 2] = 0;

		pFsLut[(i + 512) * 3 + 0] = 0;
		pFsLut[(i + 512) * 3 + 1] = 255;
		pFsLut[(i + 512) * 3 + 2] = i;

		pFsLut[(i + 768) * 3 + 0] = 0;
		pFsLut[(i + 768) * 3 + 1] = 255 - i;
		pFsLut[(i + 768) * 3 + 2] = 255;

		pFsLut[(i + 1024) * 3 + 0] = i;
		pFsLut[(i + 1024) * 3 + 1] = 0;
		pFsLut[(i + 1024) * 3 + 2] = 255;

		pFsLut[(i + 1280) * 3 + 0] = 255;
		pFsLut[(i + 1280) * 3 + 1] = 0;
		pFsLut[(i + 1280) * 3 + 2] = 255 - i;
	}

	updateFsHeight();
}

void FadeAndScrollVisualizer::stop() {
	if (pFsLut)
		free(pFsLut);
	if (pFsHeight)
		free(pFsHeight);
}

void FadeAndScrollVisualizer::onButtonPressed(uint8_t button,
		uint8_t buttonStates) {
	switch (button) {
	case 1:
		if ((buttonStates & 2) == 2) {
			updateFsHeight();
			if (++mode >= 2)
				mode = 0;
		} else {
			fsSpeed -= 1;
			if (fsSpeed <= 1)
				fsSpeed = 1;
		}
		break;
	case 2:
		fsSpeed += 1;
		if (fsSpeed >= 40)
			fsSpeed = 40;
		break;
	case 3:
		if ((buttonStates & 8) == 8) {
			direction = ((direction == -1) ? 1 : -1);
		} else {
			fsZoom -= 5;
			if (fsZoom <= 1)
				fsZoom = 1;
			else
				updateFsHeight();
		}
		break;
	case 4:
		fsZoom += 5;
		if (fsZoom >= 250)
			fsZoom = 250;
		else
			updateFsHeight();
		break;
	}
}
