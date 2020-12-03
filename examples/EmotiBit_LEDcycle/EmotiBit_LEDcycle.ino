/*
This code example can be used to run/test the onBoard Led's on the EmotiBit.
The code cycles through the RED, BLUE and YELLOW led's.
It uses the Alternate I2C, which is used by default on the EmotiBit to communicate with teh NCP5623 led driver.
*/

#include "EmotiBit_NCP5623.h"

TwoWire myWire(&sercom1, 11, 13);
NCP5623 led;

void setup() {
	Serial.begin(9600);
	// To enable the MOSFET on the EmotiBit
	pinMode(6, OUTPUT);
	digitalWrite(6, LOW);
	while(!Serial.available())
	{
		Serial.println("Enter a character to start the example.");
		delay(500);
	}
	Serial.read();// remove the character from the buffer
	// waits for input in seial monitor
	// If using Native I2C
	// Wire.begin();
	// Wire.setClock(100000);
	// led.begin();
	// If Using Secondary I2C on Adafruit Feather M0 WiFi
	myWire.begin();
	pinPeripheral(11, PIO_SERCOM);
	pinPeripheral(13, PIO_SERCOM);
	myWire.setClock(100000);
	if(!led.begin(myWire))
	{
		Serial.println("Sensor not found on the I2C line");
		while(1);
	}
	else
	{
		Serial.println("Sensor Found. Begining execution");
	}

	Serial.println("exiting Setup");
	// uncomment to Enable debugging messages
	//led.enableDebugging();
	// set the current output level
	led.setCurrent(26);
}

void loop() {	
	// Setting LED #2 to the PWM level 2
	led.setLEDpwm(2, 2);
	for (int ledPos = 1; ledPos < 4; ledPos++) {
		Serial.print("LED:\t");
		Serial.println(ledPos);
		led.setLED(ledPos, !led.getLED(ledPos));
		delay(500);
	}
	
}