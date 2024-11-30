#ifndef TOF_h
#define TOF_h

#include "../Adafruit_VL6180X-master/Adafruit_VL6180X.h"
#include "../General/DefineEnum.h" //Warum will VScode nur 2 "."? Es sollten 3 sein!
#include "../Portexpander/src/SparkFun_I2C_Mux_Arduino_Library.h"

class TOFonMux{
    public:
    TOFonMux(QWIICMUX expander, uint8_t pin);


    private:
    QWIICMUX expander;
    uint8_t pin;
};

#endif