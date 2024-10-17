#include "General.h"


bool Robot::init() {
    Serial.begin(9600);
    //Expander
    topExpander1.attach(Wire);
    topExpander2.attach(Wire);
    bottomExpander1.attach(Wire1);
    bottomExpander2.attach(Wire1);

    topExpander1.setDeviceAddress(0x20);
    topExpander2.setDeviceAddress(0x21);
    bottomExpander1.setDeviceAddress(0x23);
    bottomExpander2.setDeviceAddress(0x24);

    topExpander1.config(TCA9534::Config::IN);
    topExpander2.config(TCA9534::Config::IN);
//    topExpander2.config(DISPLAY_LIGHT, TCA9534::Config::OUT);
//    topExpander2.config(BLUETOOTH, TCA9534::Config::OUT);
    bottomExpander1.config(TCA9534::Config::OUT);
//    bottomExpander1.config(AUX_SW1, TCA9534::Config::IN);
//    bottomExpander1.config(AUX_SW2, TCA9534::Config::IN);
    
    bottomExpander2.config(TCA9534::Config::OUT);

    topExpander1.polarity(TCA9534::Polarity::ORIGINAL);
    topExpander2.polarity(TCA9534::Polarity::ORIGINAL);
    bottomExpander1.polarity(TCA9534::Polarity::ORIGINAL);
    bottomExpander2.polarity(TCA9534::Polarity::ORIGINAL);
    pinMode(3, INPUT); //Startswitchpin = 3

    //Motors & Movement
    motorExpander.attach(Wire1);
    motorExpander.setDeviceAddress(0x22);
    motorExpander.config(TCA9534::Config::OUT);
    motorExpander.polarity(TCA9534::Polarity::ORIGINAL);

    Motor motors[4];
    motors[1] = Motor(MOTOR_BACK_LEFT_IN1, MOTOR_BACK_LEFT_IN2, MOTOR_BACK_LEFT_PWM, &motorExpander);
    motors[2] = Motor(MOTOR_BACK_RIGHT_IN1, MOTOR_BACK_RIGHT_IN2, MOTOR_BACK_RIGHT_PWM, &motorExpander);
    motors[3] = Motor(MOTOR_FRONT_LEFT_IN1, MOTOR_FRONT_LEFT_IN2, MOTOR_FRONT_LEFT_PWM, &motorExpander);
    motors[4] = Motor(MOTOR_FRONT_RIGHT_IN1, MOTOR_FRONT_RIGHT_IN2, MOTOR_FRONT_RIGHT_PWM, &motorExpander);
    move = Movement(motors);
    //BNO
    if (!bno.begin()){
        Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
        while (1);
    } 
    //-----------
    return 1;
}

void Robot::processExpanderInputs(){
    topExpander1Bits = topExpander1.input();
    topExpander2Bits = topExpander2.input();
    bottomExpander1Bits = bottomExpander1.input();
    bottomExpander2Bits = bottomExpander2.input();
}
/*
@description Time passed since last use of this function (in microsec)
@warning Will break after Teensy is on for 70min
*/
long Robot::deltaTime(){
    long oldMicros = lastMicros;
    lastMicros = micros();
    return lastMicros - oldMicros;
}

bool Robot::getExpanderBit(Mutliplexer expander, uint8_t bit) {
    switch(expander){
        case MULTIPLEXER_TOP_1:
            return topExpander1Bits & (1 << bit);
        case MULTIPLEXER_TOP_2:
            return topExpander2Bits & (1 << bit);
        case MULTIPLEXER_BOTTOM_1:
            return bottomExpander1Bits & (1 << bit);
        case MULTIPLEXER_BOTTOM_2:
            return bottomExpander2Bits & (1 << bit);
        default:
            return 0;
    }
}
bool Robot::readSwitch(Switch sw) {
    if(sw == Switch::StartSwitch){
        return digitalReadFast(3); //Startswitchpin = 3
    } else {
        return getExpanderBit(MULTIPLEXER_TOP_1, sw);
    }
}
bool Robot::readButton(Buttons button) {
    switch (button) {
    case BUTTON5:
    case BUTTON6:
        return !getExpanderBit(MULTIPLEXER_TOP_2, button + 1); // Frag die Dogs warum "+1" und "+3"
    default:
        return !getExpanderBit(MULTIPLEXER_TOP_1, button + 3); // Invertierung damit gedrückt = true und nicht gedrückt = false
    }
}