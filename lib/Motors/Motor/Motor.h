#ifndef Motor_h
#define Motor_h

#include "../TCA9534-master/TCA9534.h"

class Motor{
public:

    Motor(uint8_t IN1, uint8_t IN2, uint8_t pwmPin, TCA9534* motorExpander);

    /*
    @param Speed from 0-255
    */
    uint8_t speed; //0-255
    void processOutput();
private:
    TCA9534* motorExpander;
    uint8_t IN1Pin;
    uint8_t IN2Pin;
    uint8_t pwmPin;
};


#endif