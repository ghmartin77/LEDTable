/*
 * TestPatternApp.cpp
 *
 *  Created on: 27.08.2016
 *      Author: anonymous
 */

#include "TestPatternApp.h"

TestPatternApp::TestPatternApp(LEDMatrix* pLEDMatrix) :
		App(pLEDMatrix) {
	name = "Test Pattern";

	brightness = pLEDMatrix->getBrightness();
}

TestPatternApp::~TestPatternApp() {

}

void TestPatternApp::renderTestPattern() {
	uint8_t image[12 * 12 * 3 + 1] =
			"fffTTTRRRbbbkkk^^^WWWkkkgggcccOOO[[[]]]ZZZbbN_i\\OgdDZDU<VgOP`T`XXn<<<QQQ[[[\316\316\323\304\302\35o\304P\0\303\253\2\275\0\311\0\312\303\0\4`\0_\0\0\273\14\14\13NNNddd\312\312\317\304\303!p\302Q\0\302\253\4\272\2\305\0\306\277\0\4^\0^\0\0\267\0\0\0UUUmmm779==\14OhG-ha\\\224\\\225W\226\277\204\206\241\203\241\256\256\350\260\260\260jjjvvv\6\6\6\16\16\16BBBBBB\201\201\201~~~\272\272\272\272\272\272\375\375\375\377\377\377sssiii\377\377\377\367\367\367\0\0\0\10\10\10\7\7\7\3\3\3\2\2\2\7\3\0\364\360\344\370\366\360ffglll\377\377\377\240\240\240\203\204\203\232\233\233\213\213\213\225\225\225\224\224\223\276\223!\271\216\35\244\217Vkkkhkj\377\225\273\376\220\264\354\217\256\324\216\245\274\214\234\247\214\225\225\222\223\266\266\266\266\266\266\270\270\270]]]eee\211@\351\1776\335l-\272R$\2159\30a\36\155\24\21\27^^^^^^lll[[[XXXDDCMMMPPOVVUFGF???UUUVVVccc>>>LLLXXXDDDBBBQQQcccTTTMMMcccVVVTTT>>>LLL";
	uint8_t image2[12 * 12 * 3 + 1] =
			"\300\300\302\300\300\177\303\300\1^\300c\0\300\314\0\300\11\37\241\37\266"
					"\13\274\300\1o\277\0\0" "1\0\217\0\0\300\300\300\302\300\300\177\303\300\1"
					"^\300c\0\300\314\0\300\11\37\241\37\266\13\274\300\1o\277\0\0" "1\0\217\0"
					"\0\300\300\300\302\300\300\177\303\300\1^\300c\0\300\314\0\300\11\37\241"
					"\37\266\13\274\300\1o\277\0\0" "1\0\217\0\0\300\300\300\302\300\300\177\303"
					"\300\1^\300c\0\300\314\0\300\11\37\241\37\266\13\274\300\1o\277\0\0" "1\0"
					"\217\0\0\300\300\300\302\300\300\177\303\300\1^\300c\0\300\314\0\300\11\37"
					"\241\37\266\13\274\300\1o\277\0\0" "1\0\217\0\0\300\300\300\302\300\300\177"
					"\303\300\1^\300c\0\300\314\0\300\11\37\241\37\266\13\274\300\1o\277\0\0" "1"
					"\0\217\0\0\300\300\300\302\300\300\177\303\300\1^\300c\0\300\314\0\300\11"
					"\37\241\37\266\13\274\300\1o\277\0\0" "1\0\217\0\0\300\300\300\302\300\300"
					"\177\303\300\1^\300c\0\300\314\0\300\11\37\241\37\266\13\274\300\1o\277\0"
					"\0" "1\0\217\0\0\300\307\307\302\306\306~\312\306\0^\306b\0\306\315\0\306"
					"\10\40\245\37\274\5\274\306\0o\305\0\0.\0\217\0\0\300\2\10\254\7\15z:=>\210"
					"8\207\273\21\301\40\17+\24(2\6\236\234\13dc\25\16\16}}|\241\241\240\0!K\0"
					"\40L\355\360\364\374\374\375rQ\2303\0k#\11?\22\23\17\17\17\16\23\23\23\25"
					"\26\25\23\23\22\0!L\1!L\354\356\361\372\372\374rQ\2312\0k#\12?\22\24\21\17"
					"\17\17\23\23\23\26\26\26\23\23\23";

	switch (patternType) {
	case 1:
		for (int y = 0; y < 12; ++y) {
			for (int x = 0; x < 12; ++x) {
				pMatrix->setPixel(x, y, image2[(x + y * 12) * 3],
						image2[(x + y * 12) * 3 + 1],
						image2[(x + y * 12) * 3 + 2]);
			}
		}
		break;
	case 2:
		pMatrix->fill(255, 0, 0);
		break;
	case 3:
		pMatrix->fill(0, 255, 0);
		break;
	case 4:
		pMatrix->fill(0, 0, 255);
		break;
	case 5:
		pMatrix->fill(255, 255, 0);
		break;
	case 6:
		pMatrix->fill(0, 255, 255);
		break;
	case 7:
		pMatrix->fill(255, 0, 255);
		break;
	case 8:
		pMatrix->fill(255, 255, 255);
		break;
	case 9:
		for (int y = 0; y < 12; ++y) {
			for (int x = 0; x < 12; ++x) {
				if ((y & 1) == 0) {
					if ((x & 1) == 0) {
						pMatrix->setPixel(x, y, 0, 0, 0);
					} else {
						pMatrix->setPixel(x, y, 255, 255, 255);
					}
				} else {
					if ((x & 1) == 0) {
						pMatrix->setPixel(x, y, 255, 255, 255);
					} else {
						pMatrix->setPixel(x, y, 0, 0, 0);
					}
				}
			}
		}
		break;
	case 10:
		for (int y = 0; y < 12; ++y) {
			for (int x = 0; x < 12; ++x) {
				if ((y & 1) == 1) {
					if ((x & 1) == 0) {
						pMatrix->setPixel(x, y, 0, 0, 0);
					} else {
						pMatrix->setPixel(x, y, 255, 255, 255);
					}
				} else {
					if ((x & 1) == 0) {
						pMatrix->setPixel(x, y, 255, 255, 255);
					} else {
						pMatrix->setPixel(x, y, 0, 0, 0);
					}
				}
			}
		}
		break;
	default:
		for (int y = 0; y < 12; ++y) {
			for (int x = 0; x < 12; ++x) {
				pMatrix->setPixel(x, y, image[(x + y * 12) * 3],
						image[(x + y * 12) * 3 + 1],
						image[(x + y * 12) * 3 + 2]);
			}
		}
	}
	pMatrix->update();
}

void TestPatternApp::start() {
	pMatrix->setBrightness(brightness);

	renderTestPattern();
}

void TestPatternApp::stop() {
}

void TestPatternApp::onButtonPressed(uint8_t button, uint8_t buttonStates) {
	switch (button) {
	case 1:
		brightness -= 0.1f;
		if (brightness <= 0.1f)
			brightness = 0.1f;
		pMatrix->setBrightness(brightness);
		pMatrix->update();
		break;
	case 2:
		brightness += 0.1f;
		if (brightness >= 1.0f)
			brightness = 1.0f;
		pMatrix->setBrightness(brightness);
		pMatrix->update();
		break;
	case 3:
		patternType += 1;
		if (patternType > 10)
			patternType = 0;
		renderTestPattern();
		break;
	case 4:
		pMatrix->update();
		break;
	}
}

void TestPatternApp::run() {
	delay(10);
}
