#include "Motor.h"
#include "../TCA9534-master/TCA9534.h"

Motor::Motor(uint frequency, uint8_t IN1, uint8_t IN2, uint8_t pwmPin, TCA9534* motorExpander, double pwmFactor){
    this->IN1Pin = IN1;
    this->IN2Pin = IN2;
    this->pwmPin = pwmPin;
    this->motorExpander = motorExpander;
    this->pwmFactor = pwmFactor;
    pinMode(pwmPin, OUTPUT);
    analogWriteFrequency(pwmPin, frequency);
}

void Motor::processOutput(){
    //Speed
    short pwmOut;
    pwmOut = speed * pwmFactor;
    //Direction
    uint8_t stateIn1;
    uint8_t stateIn2;
    if(pwmOut > 0){
        stateIn1 = LOW;
        stateIn2 = HIGH;
    } else if(pwmOut < 0){
        stateIn1 = HIGH;
        stateIn2 = LOW;
    } else {
        stateIn1 = LOW;
        stateIn2 = LOW;
        pwmOut = 255; //If pwmOut = 0: Free Running
    }
    pwmOut = min(pwmOut, 255); //Limits pwmOut to 255 or lower
    pwmOut = max(pwmOut, -255); //Limits pwmOut to -255 or higher
    //Output
    this->motorExpander->output(this->IN1Pin, stateIn1);
    this->motorExpander->output(this->IN2Pin, stateIn2);
    analogWrite(this->pwmPin, abs(pwmOut));
}