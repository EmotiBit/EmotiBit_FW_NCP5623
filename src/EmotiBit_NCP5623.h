#include <Wire.h>
#include "Arduino.h"
#include "wiring_private.h"
#define NCP5623_DEFAULT_ADDR 0x38

#define NCP5623_REG_ILED 1
#define NCP5623_REG_CHANNEL_BASE 2
#define NCP_5623_NUM_LED 3

class NCP5623
{
    public:
        //Constructor
		NCP5623();
        
        /*
        * Enum for Identifying which LED is switched ON 
        */
        typedef enum{
            LED1 = 1,
            LED2,
            LED3,
        }LED;
        /*
        * Initializes the I2C interface(user defined, but Wire by Default)
        */
        void begin(TwoWire &wirePort = Wire);


        void setCurrent(uint8_t iled = 31);

        /*
        * Set or unSet an LED
        * Inputs: Led Position and Intensity
        */
        void setLED(uint8_t ledPosition = -1, bool state = false);
		bool getLED(uint8_t ldePosition = -1);
		uint8_t getLEDpwm(uint8_t ledPosition);
		void setLEDpwm(uint8_t ledPosition, uint8_t pwm_val);
		void enableDebugging(Stream &debugPort = Serial);
    private:

		
        uint8_t _deviceAddress;
        TwoWire *_i2cPort;
		bool _stateLed[NCP_5623_NUM_LED];
		//bool _stateLed1;
		//bool _stateLed2;
		//bool _stateLed3;
		uint8_t _pwmValLed[NCP_5623_NUM_LED];
		//uint8_t _pwmValLed1;
		//uint8_t _pwmValLed2;
		//uint8_t _pwmValLed3;
		Stream *_debugPort; //The stream to send debug messages to if enabled
		boolean _printDebug = false; //Flag to print debugging variables

};

