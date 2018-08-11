#include <Arduino.h>

#include <SPI.h>

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Udp.h>

#include "defines.h"
#include "LEDMatrix.h"
#include "LEDTableRC.h"

#include "App.h"
#include "NoneApp.h"
#include "VisualizerApp.h"
#include "DMXRendererApp.h"
#include "TetrisApp.h"
#include "SnakeApp.h"
#include "ConnectFourApp.h"
#include "StarshipApp.h"
#include "PongApp.h"
#include "TestPatternApp.h"

#include "FadeAndScrollVisualizer.h"
#include "FallingObjectsVisualizer.h"
#include "RotatingRainbowVisualizer.h"
#include "NoiseVisualizer.h"
#include "NoiseWithPaletteVisualizer.h"

#include "CapacitiveButton.h"
#include "InputController.h"

#include <ArduinoOTA.h>

#ifdef DEBUG
WiFiServer server(4711);
WiFiClient serverClient;
#endif

LEDMatrix matrix(D3, D0);
//ESP8266WebServer server(80);
//LEDTableRC remoteControl;
InputController inputController;

App* allApps[32];
uint8_t noOfApps = 0;

App* currentApp;
int currentAppNo = 0;

/*
 void handleNotFound() {
 String message = "File Not Found\n\n";
 message += "URI: ";
 message += server.uri();
 message += "\nMethod: ";
 message += (server.method() == HTTP_GET) ? "GET" : "POST";
 message += "\nArguments: ";
 message += server.args();
 message += "\n";

 for (uint8_t i = 0; i < server.args(); i++) {
 message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
 }

 server.send(404, "text/plain", message);
 }
 */

void registerApp(App* pApp) {
	allApps[noOfApps] = pApp;
	noOfApps++;
}

void setCurrentApp(uint8_t appNo) {
	if (appNo >= noOfApps || allApps[appNo] == currentApp)
		return;

	if (currentApp)
		currentApp->stop();

	currentApp = allApps[appNo];

	Serial.print("Switched running App to ");
	Serial.println(currentApp->getName());

	currentApp->start();
}

boolean tryConnectToWiFi(const char* SSID, const char* password) {
	boolean toggle = true;
	Serial.print("\nConnecting to WiFi");
	unsigned long int millisToStop = millis() + 10000;
	WiFi.begin(SSID, password);
	while (WiFi.status() != WL_CONNECTED && millis() < millisToStop) {
		if (toggle) {
			matrix.setPixel(5, 5, 255, 255, 0);
			matrix.setPixel(6, 6, 255, 255, 0);
			matrix.setPixel(5, 6, 0, 0, 0);
			matrix.setPixel(6, 5, 0, 0, 0);
		} else {
			matrix.setPixel(5, 6, 255, 255, 0);
			matrix.setPixel(6, 5, 255, 255, 0);
			matrix.setPixel(5, 5, 0, 0, 0);
			matrix.setPixel(6, 6, 0, 0, 0);
		}
		matrix.update();
		toggle = !toggle;
		Serial.print(".");
		delay(250);
	}

	return WiFi.status() == WL_CONNECTED;
}

void connectToWiFi() {
	if (!tryConnectToWiFi(WIFI_SSID, WIFI_PASSWORD)) {
		tryConnectToWiFi(WIFI_SSID2, WIFI_PASSWORD2);
	}

	if (WiFi.status() == WL_CONNECTED) {
		Serial.println("");
		Serial.println("WiFi connected");
		Serial.print("IP address: ");
		Serial.println(WiFi.localIP());

		matrix.clear(false);
		uint8_t smiley[][2] = { { 2, 0 }, { 3, 0 }, { 4, 0 }, { 5, 0 },
				{ 1, 1 }, { 6, 1 }, { 0, 2 }, { 2, 2 }, { 5, 2 }, { 7, 2 }, { 0,
						3 }, { 7, 3 }, { 0, 4 }, { 2, 4 }, { 5, 4 }, { 7, 4 }, {
						0, 5 }, { 3, 5 }, { 4, 5 }, { 7, 5 }, { 1, 6 },
				{ 6, 6 }, { 2, 7 }, { 3, 7 }, { 4, 7 }, { 5, 7 } };

		for (int i = 0; i < sizeof(smiley) / sizeof(smiley[0]); ++i) {
			matrix.setPixel(2 + smiley[i][0], 2 + smiley[i][1], 0x0000ff00);
		}
	} else {
		Serial.println("");
		Serial.println("WiFi connection failed");

		matrix.clear(false);
		uint8_t smiley[][2] = { { 2, 0 }, { 3, 0 }, { 4, 0 }, { 5, 0 },
				{ 1, 1 }, { 6, 1 }, { 0, 2 }, { 2, 2 }, { 5, 2 }, { 7, 2 }, { 0,
						3 }, { 7, 3 }, { 0, 4 }, { 3, 4 }, { 4, 4 }, { 7, 4 }, {
						0, 5 }, { 2, 5 }, { 5, 5 }, { 7, 5 }, { 1, 6 },
				{ 6, 6 }, { 2, 7 }, { 3, 7 }, { 4, 7 }, { 5, 7 } };

		for (int i = 0; i < sizeof(smiley) / sizeof(smiley[0]); ++i) {
			matrix.setPixel(2 + smiley[i][0], 2 + smiley[i][1], 0x00ff0000);
		}
	}

	matrix.update();

	delay(2000);
	matrix.clear(true);
}

void setupOTA() {
	ArduinoOTA.setPort(8266);
	ArduinoOTA.setHostname("LEDTable");
	ArduinoOTA.onStart([]() {
		Serial.println("Start");
	});
	ArduinoOTA.onEnd([]() {
		Serial.println("\nEnd");
	});
	ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
		Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
	});
	ArduinoOTA.onError([](ota_error_t error) {
		Serial.printf("Error[%u]: ", error);
		if (error == OTA_AUTH_ERROR)
		Serial.println("Auth Failed");
		else
		if (error == OTA_BEGIN_ERROR)
		Serial.println("Begin Failed");
		else
		if (error == OTA_CONNECT_ERROR)
		Serial.println("Connect Failed");
		else
		if (error == OTA_RECEIVE_ERROR)
		Serial.println("Receive Failed");
		else
		if (error == OTA_END_ERROR)
		Serial.println("End Failed");
	});
	ArduinoOTA.begin();
}

void onEvent(uint8_t* data) {
	if (data[0] == 1) {
		matrix.rotateCW();
	}
	if (data[0] == 2) {
		setCurrentApp(data[1]);
	}

	if (data[0] == 3) {
		if (currentApp) {
			currentApp->onButtonPressed(data[1], data[2]);
		}
	}

	if (data[0] == 100) {
		if (++currentAppNo > noOfApps)
			currentAppNo = 0;
		setCurrentApp(currentAppNo);
		delay(500);
	}
}

//void startWebServer() {
//	server.onNotFound(handleNotFound);
//	server.begin();
//	Serial.println("HTTP server started");
//}

void setup() {
	delay(1000);
	Serial.begin(115200);
	Serial.println("\n\n\n\n\rStarting LED Table 3.0");

	matrix.init();
	matrix.clear();
	matrix.setRotation(LEDMatrix::ROTATION_270);
	matrix.setCalibration(0.72f, 1.0f, 0.4f);
	matrix.setBrightness(0.1f);

	// Turn off blue status LED
	digitalWrite(D4, LOW);

	connectToWiFi();
	matrix.clear();
	//startWebServer();
	setupOTA();

	delay(200);

	registerApp(new NoneApp(&matrix));

	VisualizerApp* visApp1 = new VisualizerApp(&matrix);
	visApp1->setVisualizer(0, new FadeAndScrollVisualizer(10, 30));
	registerApp(visApp1);

	VisualizerApp* visApp3 = new VisualizerApp(&matrix);
	visApp3->setVisualizer(0, new RotatingRainbowVisualizer());
	registerApp(visApp3);

	VisualizerApp* visApp2 = new VisualizerApp(&matrix);
	visApp2->setVisualizer(0, new FallingObjectsVisualizer(0));
	visApp2->setVisualizer(1, new FallingObjectsVisualizer(1));
	visApp2->setVisualizer(2, new FallingObjectsVisualizer(2));
	visApp2->setVisualizer(3, new FallingObjectsVisualizer(3));
	registerApp(visApp2);

	VisualizerApp* visApp4 = new VisualizerApp(&matrix);
	visApp4->setVisualizer(0, new NoiseVisualizer());
	registerApp(visApp4);

	VisualizerApp* visApp5 = new VisualizerApp(&matrix);
	visApp5->setVisualizer(0, new NoiseWithPaletteVisualizer());
	registerApp(visApp5);

	registerApp(new TetrisApp(&matrix));
	registerApp(new ConnectFourApp(&matrix));
	registerApp(new SnakeApp(&matrix));
	registerApp(new StarshipApp(&matrix));
	registerApp(new PongApp(&matrix));
	registerApp(new TestPatternApp(&matrix));
	registerApp(new DMXRendererApp(&matrix));

//	remoteControl.begin();
//	remoteControl.setEventCallback(onEvent);

	inputController.setEventCallback(onEvent);

#ifdef DEBUG
	server.begin();
	server.setNoDelay(true);
#endif

	setCurrentApp(0);
}

void loop() {
#ifdef DEBUG
	if (server.hasClient()) {

		if (!serverClient || !serverClient.connected()) {
			if (serverClient)
			serverClient.stop();
			serverClient = server.available();
		}
		WiFiClient serverClient = server.available();
		serverClient.stop();
	}
#endif

	ArduinoOTA.handle();

//	remoteControl.update();
	inputController.update();

	if (currentApp)
		currentApp->run();
}

