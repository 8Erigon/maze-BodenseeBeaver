#ifndef TOF_h
#define TOF_h

#include "../Adafruit_VL6180X-master/Adafruit_VL6180X.h"
#include "../General/DefineEnum.h" //Warum will VScode nur 2 "."? Es sollten 3 sein!
#include "../Portexpander/src/SparkFun_I2C_Mux_Arduino_Library.h"

class TOFonMux : public Adafruit_VL6180X{
    public:
    TOFonMux(uint8_t pinOnMux, uint8_t expanderAddress = QWIIC_MUX_DEFAULT_ADDRESS, TwoWire &wirePort = Wire) : Adafruit_VL6180X() {
        expander->begin(expanderAddress, wirePort);
        this->pin = pinOnMux;
    };


    private:
    uint8_t pin;
    QWIICMUX *expander;

};

#endif