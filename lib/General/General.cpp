#include "General.h"

void Robot::process(){
    Serial.println("Start processing");        
    processExpanderInputs(); 
    Serial.println("expander");
    bno.getEvent(&orientation, Adafruit_BNO055::VECTOR_EULER);
    Serial.println("bno orientation");
    bno.getEvent(&acceleration, Adafruit_BNO055::VECTOR_LINEARACCEL);
    Serial.println("bno acceleration");
    deltaTime = computeDeltaTime();
    Serial.println("delta time");
    move.process();
    Serial.println("movement");
}

void Robot::setRunning(bool isRunning){
    if(isRunning){
        move.manuellSteering = false;
    } else {
        move.manuellSteering = true;
        for(int i = 0; i < 4; i++){
            motors[i].speed = 0;
            motors[i].processOutput();
        }
    }
}

Robot::Robot() : //Member Initializer List
    motors{Motor(MOTOR_FREQUENCY, MOTOR_FRONT_LEFT_IN1, MOTOR_FRONT_LEFT_IN2, MOTOR_FRONT_LEFT_PWM, &motorExpander),
        Motor(MOTOR_FREQUENCY, MOTOR_BACK_LEFT_IN1, MOTOR_BACK_LEFT_IN2, MOTOR_BACK_LEFT_PWM, &motorExpander),
        Motor(MOTOR_FREQUENCY, MOTOR_FRONT_RIGHT_IN1, MOTOR_FRONT_RIGHT_IN2, MOTOR_FRONT_RIGHT_PWM, &motorExpander),
        Motor(MOTOR_FREQUENCY, MOTOR_BACK_RIGHT_IN1, MOTOR_BACK_RIGHT_IN2, MOTOR_BACK_RIGHT_PWM, &motorExpander)},
    move{Movement(motors[0], orientation)}
    {
    Serial.begin(9600);
    //Expander
    Wire.begin();
    Wire1.begin();
    topExpander1.attach(Wire);
    topExpander2.attach(Wire);
    bottomExpander1.attach(Wire1);
//    bottomExpander2.attach(Wire1);

    topExpander1.setDeviceAddress(0x20);
    topExpander2.setDeviceAddress(0x21);
    bottomExpander1.setDeviceAddress(0x23);
    bottomExpander2.setDeviceAddress(0x24);

    topExpander1.config(TCA9534::Config::IN);
    topExpander2.config(TCA9534::Config::IN);
    topExpander2.config(5, TCA9534::Config::OUT); //Display Light
//    topExpander2.config(4, TCA9534::Config::OUT); //Bluetooth
    bottomExpander1.config(TCA9534::Config::OUT);
    bottomExpander1.config(0, TCA9534::Config::IN); //AUX_SW1
    bottomExpander1.config(1, TCA9534::Config::IN); //AUX_SW2
//    bottomExpander2.config(TCA9534::Config::OUT);

    topExpander1.polarity(TCA9534::Polarity::ORIGINAL);
    topExpander2.polarity(TCA9534::Polarity::ORIGINAL);
    bottomExpander1.polarity(TCA9534::Polarity::ORIGINAL);
//    bottomExpander2.polarity(TCA9534::Polarity::ORIGINAL);
    pinMode(3, INPUT); //Startswitchpin = 3
    pinMode(10, OUTPUT); //ADC pin

    //Motors & Movement
    motorExpander.attach(Wire1);
    motorExpander.setDeviceAddress(0x22);
    motorExpander.config(TCA9534::Config::OUT);
    motorExpander.polarity(TCA9534::Polarity::ORIGINAL);

    //BNO
    if (!bno.begin()){
        Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    } 
}

void Robot::processExpanderInputs(){
    topExpander1Bits = topExpander1.input();
    topExpander2Bits = topExpander2.input();
    bottomExpander1Bits = bottomExpander1.input();
//    bottomExpander2Bits = bottomExpander2.input();
}

/*
@details Time passed since last use of this function (in microsec)
@warning Will break after Teensy is on for 70min
*/
long Robot::computeDeltaTime(){
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

void Robot::computeCoordinates(){
    
}