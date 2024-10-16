#ifndef Motor_h
#define Motor_h

#include "../TCA9534-master/TCA9534.h"

class Motor{
public:

    Motor(uint8_t _IN1, uint8_t _IN2, uint8_t _pwmPin, TCA9534* _motorExpander);

    void setSpeed(int _speed);
    void processOutput();
private:
    int speed;

    TCA9534* motorExpander;
    uint8_t IN1Pin;
    uint8_t IN2Pin;
    uint8_t pwmPin;
};


#endif