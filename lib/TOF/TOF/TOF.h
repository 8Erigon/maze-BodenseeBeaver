#ifndef TOF_h
#define TOF_h

#include "../Adafruit_VL6180X-master/Adafruit_VL6180X.h"
#include "../General/DefineEnum.h" //Warum will VScode nur 2 "."? Es sollten 3 sein!
#include "../Portexpander/src/SparkFun_I2C_Mux_Arduino_Library.h"

class TOFonMux : public Adafruit_VL6180X{
    public:
    TOFonMux(uint8_t pinOnMux, QWIICMUX *expander);
    TOFonMux();

    uint8_t range;
    private:
    uint8_t pin;
    QWIICMUX *expander;

};

#endif