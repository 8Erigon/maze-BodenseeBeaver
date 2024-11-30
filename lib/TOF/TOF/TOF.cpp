#include "TOF.h"

TOFonMux::TOFonMux(QWIICMUX expander, uint8_t pin){
    this->expander = expander;
    this->pin = pin;
}