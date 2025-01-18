#ifndef COLOR_SENSOR_H
#define COLOR_SENSOR_H

#include <Adafruit_TCS34725.h>
#include "../Portexpander/src/SparkFun_I2C_Mux_Arduino_Library.h"

class ColorSensorOnMux{
    public:
    /*
    @details Mux is short for Expander
    */
    ColorSensorOnMux(uint8_t pinOnMux, QWIICMUX &Expander, TwoWire &theWire = Wire, uint8_t addr = TCS34725_ADDRESS);
    ColorSensorOnMux();

    boolean begin(uint8_t addr = TCS34725_ADDRESS, TwoWire *theWire = &Wire);
    boolean init();

    void setIntegrationTime(uint8_t it);
    void setGain(tcs34725Gain_t gain);
    void getRawData(uint16_t *r, uint16_t *g, uint16_t *b, uint16_t *c);
    void getRGB(float *r, float *g, float *b);
    void getRawDataOneShot(uint16_t *r, uint16_t *g, uint16_t *b, uint16_t *c);
    uint16_t calculateColorTemperature(uint16_t r, uint16_t g, uint16_t b);
    uint16_t calculateColorTemperature_dn40(uint16_t r, uint16_t g, uint16_t b,
                                          uint16_t c);
    uint16_t calculateLux(uint16_t r, uint16_t g, uint16_t b);
    void write8(uint8_t reg, uint8_t value);
    uint8_t read8(uint8_t reg);
    uint16_t read16(uint8_t reg);
    void setInterrupt(boolean flag);
    void clearInterrupt();
    void setIntLimits(uint16_t l, uint16_t h);
    void enable();
    void disable();

    private:
    uint8_t pin;
    QWIICMUX *expander;
    Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X);
    
};

#endif