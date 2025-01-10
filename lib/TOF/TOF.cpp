#include "TOF.h"

TOFonMux::TOFonMux(uint8_t pinOnMux, QWIICMUX &expander, TwoWire &I2C_bus) : Adafruit_VL6180X() {
    this->expander = &expander;
    this->pin = pinOnMux;
    Serial.println(begin(&I2C_bus));
};

TOFonMux::TOFonMux(){
    this->expander = NULL;
    this->pin = 9; //Expander/Mux only has ports from 0-7
};

boolean TOFonMux::begin(TwoWire *theWire) {
    if(this->expander == NULL) {
        return false;
    }
    this->expander->setPort(this->pin);
    return Adafruit_VL6180X::begin(theWire);
};

boolean TOFonMux::setAddress(uint8_t newAddr) {
    if(this->expander == NULL) {
        return false;
    }
    this->expander->setPort(this->pin);
    return Adafruit_VL6180X::setAddress(newAddr);
}

uint8_t TOFonMux::getAddress(void) {
    if(this->expander == NULL) {
        return 0;
    }
    this->expander->setPort(this->pin);
    return Adafruit_VL6180X::getAddress();
}

uint8_t TOFonMux::readRange(void) {
    if(this->expander == NULL) {
        return 0;
    }
    this->expander->setPort(this->pin);
    range = Adafruit_VL6180X::readRange();
    return range;
}

float TOFonMux::readLux(uint8_t gain) {
    if(this->expander == NULL) {
        return 0;
    }
    this->expander->setPort(this->pin);
    return Adafruit_VL6180X::readLux(gain);
}

uint8_t TOFonMux::readRangeStatus(void) {
    if(this->expander == NULL) {
        return 0;
    }
    this->expander->setPort(this->pin);
    status = Adafruit_VL6180X::readRangeStatus();
    return status;
}

boolean TOFonMux::startRange(void) {
    if(this->expander == NULL) {
        return false;
    }
    this->expander->setPort(this->pin);
    return Adafruit_VL6180X::startRange();
}

boolean TOFonMux::isRangeComplete(void) {
    if(this->expander == NULL) {
        return false;
    }
    this->expander->setPort(this->pin);
    return Adafruit_VL6180X::isRangeComplete();
}

boolean TOFonMux::waitRangeComplete(void) {
    if(this->expander == NULL) {
        return false;
    }
    this->expander->setPort(this->pin);
    return Adafruit_VL6180X::waitRangeComplete();
}

uint8_t TOFonMux::readRangeResult(void) {
    if(this->expander == NULL) {
        return 0;
    }
    this->expander->setPort(this->pin);
    return Adafruit_VL6180X::readRangeResult();
}

void TOFonMux::startRangeContinuous(uint16_t period_ms) {
    if(this->expander == NULL) {
        return;
    }
    this->expander->setPort(this->pin);
    return Adafruit_VL6180X::startRangeContinuous(period_ms);
}

void TOFonMux::stopRangeContinuous(void) {
    if(this->expander == NULL) {
        return;
    }
    this->expander->setPort(this->pin);
    return Adafruit_VL6180X::stopRangeContinuous();
}

void TOFonMux::setOffset(uint8_t offset) {
    if(this->expander == NULL) {
        return;
    }
    this->expander->setPort(this->pin);
    return Adafruit_VL6180X::setOffset(offset);
}

void TOFonMux::getID(uint8_t *id_ptr) {
    if(this->expander == NULL) {
        return;
    }
    this->expander->setPort(this->pin);
    return Adafruit_VL6180X::getID(id_ptr);
}