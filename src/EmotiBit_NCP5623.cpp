
#include "EmotiBit_NCP5623.h"

NCP5623::NCP5623() {}
/*
For setting the I2C port and dvice address of the chip.
It also sets the LED pwm values and Iout current value
*/
void NCP5623::begin(TwoWire &wirePort) {
    _i2cPort = &wirePort;
    _deviceAddress = NCP5623_DEFAULT_ADDR;
	// Set the Vout Current to a value before using PWM on the led's
    setCurrent(30);
	// Set the LED to a maximum 
	setLEDpwm(1, 31);
	setLEDpwm(2, 31);
	setLEDpwm(3, 31);
	setLED(1, false);
	setLED(2, false);
	setLED(3, false);

}

/*
Fucntion returns the state of the LED at the requested position
*/
bool NCP5623::getLED(uint8_t ledPosition) {

	return _stateLed[--ledPosition];
}

/*
Fucntion to set and reset a LED.
The LED is set to the defined PWM value.
*/
void NCP5623::setLED(uint8_t ledPosition, bool state) {
    uint8_t reg;
	_stateLed[ledPosition - 1] = state;
    switch(ledPosition){
        case LED1:
            reg = NCP5623_REG_CHANNEL_BASE + (ledPosition - 1);
			break;
        case LED2:
            reg = NCP5623_REG_CHANNEL_BASE + (ledPosition - 1);
			break;
        case LED3:
            reg = NCP5623_REG_CHANNEL_BASE + (ledPosition - 1);
            break;
        default:
            //TODO: INVALID case
            break;
    }
	
	if (!state) {// switch OFF led
		_i2cPort->beginTransmission(_deviceAddress);
		_i2cPort->write((reg & 0x7) << 5); 
		_i2cPort->endTransmission();
	}
	else { // Switch ON led based on set pwm level
		_i2cPort->beginTransmission(_deviceAddress);
		_i2cPort->write( ((reg & 0x7) << 5) | (getLEDpwm(ledPosition) & 0x1F));
		_i2cPort->endTransmission();
	}

}

/*
Function returns the pwm value for a LED position.
*/
uint8_t NCP5623::getLEDpwm(uint8_t ledPosition) {

	return _pwmValLed[ledPosition - 1];
}

/*
Function sets the PWM value for a led position
*/
void NCP5623::setLEDpwm(uint8_t ledPosition, uint8_t pwm_val) {
	pwm_val = (pwm_val > 31) ? 31 : pwm_val;
	pwm_val = (pwm_val < 0) ? 0 : pwm_val;
	_pwmValLed[--ledPosition] = pwm_val;
}

/*
Function sets the MAX output current.
*/
void NCP5623::setCurrent(uint8_t iled) {
    iled = (iled>30)?30:iled;
    _i2cPort->beginTransmission(_deviceAddress);
    _i2cPort->write(((NCP5623_REG_ILED&0x7)<<5)|(iled&0x1f)); // rrrvvvvv
    _i2cPort->endTransmission();
}

/*
Fucntion to print statements to the console for debugging purposes.
*/
void NCP5623::enableDebugging(Stream &debugPort)
{
	_debugPort = &debugPort;
	_printDebug = true;
}