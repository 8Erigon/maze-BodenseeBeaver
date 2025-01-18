#include "ColorSensor.h"

ColorSensorOnMux::ColorSensorOnMux(uint8_t pinOnMux, QWIICMUX &expander, TwoWire &theWire, uint8_t addr) {
    this->expander = &expander;
    this->pin = pinOnMux;
    Serial.println(begin(addr, &theWire));
}

ColorSensorOnMux::ColorSensorOnMux(){
    this->expander = NULL;
    this->pin = 9; //Expander/Mux only has ports from 0-7
}

boolean ColorSensorOnMux::begin(uint8_t addr, TwoWire *theWire) {
    if(this->expander == NULL) {
        return false;
    }
    this->expander->setPort(this->pin);
    return this->tcs.begin(addr, theWire);
}

boolean ColorSensorOnMux::init() {
    if(this->expander == NULL) {
        return false;
    }
    this->expander->setPort(this->pin);
    return this->tcs.init();
}

void ColorSensorOnMux::setIntegrationTime(uint8_t it) {
    if(this->expander == NULL) {
        return;
    }
    this->expander->setPort(this->pin);
    return this->tcs.setIntegrationTime(it);
}

void ColorSensorOnMux::setGain(tcs34725Gain_t gain) {
    if(this->expander == NULL) {
        return;
    }
    this->expander->setPort(this->pin);
    return this->tcs.setGain(gain);
}

void ColorSensorOnMux::getRawData(uint16_t *r, uint16_t *g, uint16_t *b, uint16_t *c) {
    if(this->expander == NULL) {
        return;
    }
    this->expander->setPort(this->pin);
    return this->tcs.getRawData(r, g, b, c);
}

void ColorSensorOnMux::getRGB(float *r, float *g, float *b) {
    if(this->expander == NULL) {
        return;
    }
    this->expander->setPort(this->pin);
    return this->tcs.getRGB(r, g, b);
}

void ColorSensorOnMux::getRawDataOneShot(uint16_t *r, uint16_t *g, uint16_t *b, uint16_t *c) {
    if(this->expander == NULL) {
        return;
    }
    this->expander->setPort(this->pin);
    return this->tcs.getRawDataOneShot(r, g, b, c);
}

uint16_t ColorSensorOnMux::calculateColorTemperature(uint16_t r, uint16_t g, uint16_t b) {
    if(this->expander == NULL) {
        return 0;
    }
    this->expander->setPort(this->pin);
    return this->tcs.calculateColorTemperature(r, g, b);
}

uint16_t ColorSensorOnMux::calculateColorTemperature_dn40(uint16_t r, uint16_t g, uint16_t b, uint16_t c) {
    if(this->expander == NULL) {
        return 0;
    }
    this->expander->setPort(this->pin);
    return this->tcs.calculateColorTemperature_dn40(r, g, b, c);
}

uint16_t ColorSensorOnMux::calculateLux(uint16_t r, uint16_t g, uint16_t b) {
    if(this->expander == NULL) {
        return 0;
    }
    this->expander->setPort(this->pin);
    return this->tcs.calculateLux(r, g, b);
}

void ColorSensorOnMux::write8(uint8_t reg, uint8_t value) {
    if(this->expander == NULL) {
        return;
    }
    this->expander->setPort(this->pin);
    return this->tcs.write8(reg, value);
}

uint8_t ColorSensorOnMux::read8(uint8_t reg) {
    if(this->expander == NULL) {
        return 0;
    }
    this->expander->setPort(this->pin);
    return this->tcs.read8(reg);
}

uint16_t ColorSensorOnMux::read16(uint8_t reg) {
    if(this->expander == NULL) {
        return 0;
    }
    this->expander->setPort(this->pin);
    return this->tcs.read16(reg);
}

void ColorSensorOnMux::setInterrupt(boolean flag) {
    if(this->expander == NULL) {
        return;
    }
    this->expander->setPort(this->pin);
    return this->tcs.setInterrupt(flag);
}

void ColorSensorOnMux::clearInterrupt() {
    if(this->expander == NULL) {
        return;
    }
    this->expander->setPort(this->pin);
    return this->tcs.clearInterrupt();
}

void ColorSensorOnMux::setIntLimits(uint16_t l, uint16_t h) {
    if(this->expander == NULL) {
        return;
    }
    this->expander->setPort(this->pin);
    return this->tcs.setIntLimits(l, h);
}

void ColorSensorOnMux::enable(void) {
    if(this->expander == NULL) {
        return;
    }
    this->expander->setPort(this->pin);
    return this->tcs.enable();
}

void ColorSensorOnMux::disable(void) {
    if(this->expander == NULL) {
        return;
    }
    this->expander->setPort(this->pin);
    return this->tcs.disable();
}

RGB ColorSensorOnMux::getRGB() {
    this->tcs.getRGB(&this->data.r, &this->data.g, &this->data.b);
    return this->data;
}