#ifndef TOF_h
#define TOF_h

#include "../Adafruit_VL6180X/Adafruit_VL6180X.h"
#include "../General/DefineEnum.h" 
#include "../Portexpander/src/SparkFun_I2C_Mux_Arduino_Library.h"

class TOFonMux{
    public:
    TOFonMux(uint8_t pinOnMux, QWIICMUX &expander, TwoWire &I2C_bus = Wire);
    TOFonMux();

    boolean begin(TwoWire *theWire = &Wire); //Override functions are just base function but also switch mux port before
    boolean setAddress(uint8_t newAddr);
    uint8_t getAddress(void);

    uint8_t readRange(void);
    float readLux(uint8_t gain);
    uint8_t readRangeStatus(void);

    boolean startRange(void);
    boolean isRangeComplete(void);
    boolean waitRangeComplete(void);
    uint8_t readRangeResult(void);

    void startRangeContinuous(uint16_t period_ms = 50) ;
    void stopRangeContinuous(void);
    // readRangeResult and isRangeComplete apply here is well

    void setOffset(uint8_t offset);
    void getID(uint8_t *id_ptr);

    uint8_t range;
    uint8_t status;
    private:
    uint8_t pin;
    Adafruit_VL6180X TOF = Adafruit_VL6180X();
    QWIICMUX *expander;

};

#endif