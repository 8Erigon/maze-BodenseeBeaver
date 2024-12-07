#ifndef Motor_h
#define Motor_h

#include "../TCA9534-master/TCA9534.h"
#include "DefineEnum.h"

class Motor{
public:
    Motor();
    Motor(uint frequency, uint8_t IN1, uint8_t IN2, uint8_t pwmPin, TCA9534* motorExpander, double pwmFactor = 1);

    /*
    @warning must be between -255 and 255 AFTER multiplied with pwmFactor
    */
    short speed = 0;
    /*
    @brief Call this function every loop. This processes what the motors should do
    */
    void processOutput();
private:
    TCA9534* motorExpander;
    uint8_t IN1Pin;
    uint8_t IN2Pin;
    uint8_t pwmPin;
    double pwmFactor;
};


#endif