#include <Wire.h>
#include "Arduino.h"
#include "wiring_private.h"
#define NCP5623_DEFAULT_ADDR 0x38

#define NCP5623_REG_ILED 1
#define NCP5623_REG_CHANNEL_BASE 2


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
        void setLED(uint8_t ledPosition = -1, uint8_t intensity = 31);


    private:

        uint8_t _deviceAddress;
        TwoWire *_i2cPort;

};

