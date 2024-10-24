#ifndef Motor_h
#define Motor_h

#include "../TCA9534-master/TCA9534.h"

class Motor{
public:

    Motor(uint8_t IN1, uint8_t IN2, uint8_t pwmPin, TCA9534* motorExpander);

    /*
    @brief Speed from -255 to 255
    */
    int speed;
    void processOutput();
private:
    TCA9534* motorExpander;
    uint8_t IN1Pin;
    uint8_t IN2Pin;
    uint8_t pwmPin;
};


#endif