#include "TOF.h"

TOFonMux::TOFonMux(uint8_t pinOnMux, QWIICMUX *expander) : Adafruit_VL6180X() {
    this->expander = expander;
    this->pin = pinOnMux;
};

TOFonMux::TOFonMux(){
    this->expander = NULL;
    this->pin = 9;
};