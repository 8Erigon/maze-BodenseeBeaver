#ifndef TOF_h
#define TOF_h

#include <Adafruit_VL6180X.h>
#include "../General/DefineEnum.h" 
#include "../Portexpander/src/SparkFun_I2C_Mux_Arduino_Library.h"

class TOFonMux : virtual public Adafruit_VL6180X{
    public:
    TOFonMux(uint8_t pinOnMux, QWIICMUX *expander);
    TOFonMux();

    boolean begin(TwoWire *theWire = &Wire) override; //Override functions are just base function but also switch mux port before
    boolean setAddress(uint8_t newAddr) override;
    uint8_t getAddress(void) override;

    uint8_t readRange(void) override;
    float readLux(uint8_t gain) override;
    uint8_t readRangeStatus(void) override;

    boolean startRange(void) override;
    boolean isRangeComplete(void) override;
    boolean waitRangeComplete(void) override;
    uint8_t readRangeResult(void) override;

    void startRangeContinuous(uint16_t period_ms = 50) override;
    void stopRangeContinuous(void) override;
    // readRangeResult and isRangeComplete apply here is well

    void setOffset(uint8_t offset) override;
    void getID(uint8_t *id_ptr) override;

    uint8_t range;
    private:
    uint8_t pin;
    QWIICMUX *expander;

};

#endif