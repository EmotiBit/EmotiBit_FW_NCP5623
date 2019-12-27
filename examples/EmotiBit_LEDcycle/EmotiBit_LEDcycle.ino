#include "EmotiBit_NCP5623.h"

TwoWire myWire(&sercom1, 11, 13);
NCP5623 led;

void setup() {
	Serial.begin(9600);
	pinMode(6, OUTPUT);
	digitalWrite(6, LOW);
	// waits for input in seial monitor
	while(!Serial.available());
	// If using Native I2C
	// Wire.begin();
	// Wire.setClock(100000);
	// led.begin();
	// If Using Secondary I2C on Adafruit Feather M0 WiFi
	myWire.begin();
	pinPeripheral(11, PIO_SERCOM);
	pinPeripheral(13, PIO_SERCOM);
	myWire.setClock(100000);
	led.begin(myWire);
	Serial.println("exiting Setup");
	//led.enableDebugging();
	led.setCurrent(26);
}

void loop() {	
	led.setLEDpwm(2, 2);
	for (int ledPos = 1; ledPos < 4; ledPos++) {
		Serial.print("LED:\t");
		Serial.println(ledPos);
		led.setLED(ledPos, !led.getLED(ledPos));
		delay(500);
	}
	
}