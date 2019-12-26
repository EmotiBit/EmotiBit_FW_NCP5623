
#include "EmotiBit_NCP5623.h"

//static const uint8_t NCP5623_ILED_MAP[31] = { // NCP5623_ILED_MAP[CURRENT] = REG_VALUE; // Mapped from table 3 of datasheet (https://www.onsemi.com/pub/Collateral/NCP5623-D.PDF)
//    0, 4, 17, 22, 24, 25, 26, 27, 28, 28, 28, 28, 29, 29, 29, 29, 29, 29, 29, 29, 29, 30, 30, 30, 30, 30, 30, 30, 30, 30, 31
//};

NCP5623::NCP5623() {}

void NCP5623::begin(TwoWire &wirePort) {
    _i2cPort = &wirePort;
    _deviceAddress = NCP5623_DEFAULT_ADDR;
    setCurrent(30); //TODO: Verify the functionality
}

void NCP5623::setLED(uint8_t ledPosition, uint8_t intensity) {
    uint8_t reg;
    switch(ledPosition){
        case LED1:
            reg = NCP5623_REG_CHANNEL_BASE + (ledPosition-1);
            break;
        case LED2:
            reg = NCP5623_REG_CHANNEL_BASE + (ledPosition-1);
            break;
        case LED3:
            reg = NCP5623_REG_CHANNEL_BASE + (ledPosition-1);
            break;
        default:
            //TODO: INVALID case
            break;
    }
    //intensity = intensity>>3;
    _i2cPort->beginTransmission(_deviceAddress);
    _i2cPort->write(((reg & 0x7)<<5)|(intensity & 0x1f)); // rrrvvvvv
    _i2cPort->endTransmission();

}

void NCP5623::setCurrent(uint8_t iled) {
    iled = (iled>30)?30:iled;
    _i2cPort->beginTransmission(_deviceAddress);
    _i2cPort->write(((NCP5623_REG_ILED&0x7)<<5)|(iled&0x1f)); // rrrvvvvv
    _i2cPort->endTransmission();
}
