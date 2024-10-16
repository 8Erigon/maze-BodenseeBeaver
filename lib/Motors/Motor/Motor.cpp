#include "Motor.h"
#include "../TCA9534-master/TCA9534.h"

Motor::Motor(uint8_t IN1, uint8_t IN2, uint8_t pwmPin, TCA9534* motorExpander){
    this->IN1Pin = IN1;
    this->IN2Pin = IN2;
    this->pwmPin = pwmPin;
    this->motorExpander = motorExpander;
    pinMode(pwmPin, OUTPUT);
}

void Motor::setSpeed(uint8_t speed){
    this->speed = speed;
}

void Motor::processOutput(){
    //Speed
    uint8_t pwmOut;
    pwmOut = speed;
    //Direction
    uint8_t stateIn1;
    uint8_t stateIn2;
    if(this->speed > 0){
        stateIn1 = LOW;
        stateIn2 = HIGH;
    } else if(this->speed <0){
        stateIn1 = HIGH;
        stateIn2 = LOW;
    } else {
        stateIn1 = LOW;
        stateIn2 = LOW;
        pwmOut = 255; //If pwmOut = 0: Free Running
    }
    //Output
    this->motorExpander->output(this->IN1Pin, stateIn1);
    this->motorExpander->output(this->IN2Pin, stateIn2);
    analogWrite(this->pwmPin, pwmOut);
}