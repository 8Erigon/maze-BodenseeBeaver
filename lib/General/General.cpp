#include "General.h"

 

void Robot::process(){       
    processExpanderInputs(); 
    bno.getEvent(&BNOorientation, Adafruit_BNO055::VECTOR_EULER);
    bno.getEvent(&BNOacceleration, Adafruit_BNO055::VECTOR_LINEARACCEL);
    deltaTime = computeDeltaTime();
    move.process();
    /*for(int i = 0; i<8; i++){
        TOF[i].range = TOF[i].readRange();
    }*/
    led.show();
}

void Robot::setRunning(bool isRunning){
    if(isRunning){
        move.movementControl = compass;
    } else {
        move.movementControl = manuel;
        for(int i = 0; i < 4; i++){
            motors[i].speed = 0;
            motors[i].processOutput();
        }
    }
}

Robot::Robot() : //Member Initializer List

    motors{
        Motor(MOTOR_FREQUENCY, MOTOR_FRONT_LEFT_IN1, MOTOR_FRONT_LEFT_IN2, MOTOR_FRONT_LEFT_PWM, &motorExpander, MOTOR_FRONT_LEFT_FACTOR),
        Motor(MOTOR_FREQUENCY, MOTOR_BACK_LEFT_IN1, MOTOR_BACK_LEFT_IN2, MOTOR_BACK_LEFT_PWM, &motorExpander, MOTOR_BACK_LEFT_FACTOR),
        Motor(MOTOR_FREQUENCY, MOTOR_FRONT_RIGHT_IN1, MOTOR_FRONT_RIGHT_IN2, MOTOR_FRONT_RIGHT_PWM, &motorExpander, MOTOR_FRONT_RIGHT_FACTOR),
        Motor(MOTOR_FREQUENCY, MOTOR_BACK_RIGHT_IN1, MOTOR_BACK_RIGHT_IN2, MOTOR_BACK_RIGHT_PWM, &motorExpander, MOTOR_BACK_RIGHT_FACTOR)},
    move{Movement(motors[0], orientation, acceleration)}
    {

    Serial.begin(9600);

    
    //LED
    led.begin();

    //Expander
    Wire.begin();
    Serial.println("Wire begun");
    Wire1.begin();
    Serial.println("Wire1 begun");
    topExpander1.attach(Wire);
    Serial.println("top ex 1 begun");
    topExpander2.attach(Wire);
    Serial.println("top ex 2 begun");
    bottomExpander1.attach(Wire1);
    Serial.println("bottom ex 1 begun");
//    bottomExpander2.attach(Wire1);

    Serial.println("SetAdress");
    topExpander1.setDeviceAddress(0x20);
    topExpander2.setDeviceAddress(0x21);
    bottomExpander1.setDeviceAddress(0x23);
    bottomExpander2.setDeviceAddress(0x24);

    Serial.println("config");
    topExpander1.config(TCA9534::Config::IN);
    topExpander2.config(TCA9534::Config::IN);
    topExpander2.config(5, TCA9534::Config::OUT); //Display Light
//    topExpander2.config(4, TCA9534::Config::OUT); //Bluetooth
    Serial.println("config bottom");
    bottomExpander1.config(TCA9534::Config::OUT);
    bottomExpander1.config(0, TCA9534::Config::IN); //AUX_SW1
    bottomExpander1.config(1, TCA9534::Config::IN); //AUX_SW2
//    bottomExpander2.config(TCA9534::Config::OUT);

    Serial.println("polarity");
    topExpander1.polarity(TCA9534::Polarity::ORIGINAL);
    topExpander2.polarity(TCA9534::Polarity::ORIGINAL);
    bottomExpander1.polarity(TCA9534::Polarity::ORIGINAL);
//    bottomExpander2.polarity(TCA9534::Polarity::ORIGINAL);
    pinMode(3, INPUT); //Startswitchpin = 3
    pinMode(10, OUTPUT); //ADC pin

    //Motors & Movement
    Serial.println("Motors");
    motorExpander.attach(Wire1);
    motorExpander.setDeviceAddress(0x22);
    motorExpander.config(TCA9534::Config::OUT);
    motorExpander.polarity(TCA9534::Polarity::ORIGINAL);

    //Servo
    ourServo.attach(9); 

    //BNO
    if (!bno.begin()){
        Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    } 

    //Mux
    Serial.println("Mux begin");
    Serial.println(muxBack.begin(MUXBACK_ADDR, Wire1));
    Serial.println(muxFront.begin(MUXFRONT_ADDR, Wire1));
    
    //TOF
    Serial.println("TOF begin");
    TOF[0] = TOFonMux(5, muxFront, Wire1); //FRONT RIGHT
    TOF[1] = TOFonMux(6, muxFront, Wire1); //FRONT LEFT
    TOF[2] = TOFonMux(2, muxBack, Wire1); //BACK RIGHT
    TOF[3] = TOFonMux(1, muxBack, Wire1); //BACK LEFT
    TOF[4] = TOFonMux(4, muxFront, Wire1); //RIGHT FRONT
    TOF[5] = TOFonMux(3, muxBack, Wire1); //RIGHT BACK
    TOF[6] = TOFonMux(7, muxFront, Wire1); //LEFT FRONT
    TOF[7] = TOFonMux(0, muxBack, Wire1); //LEFT BACK 
    
}

void Robot::setLedColor(uint32_t color){
    for(int i = 0; i < LED_COUNT; i++){
        led.setPixelColor(i, color);
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

void Robot::AuswurfR()     {
    move.Stop(0);
    ourServo.write(ServoResetPos);
    for (ServoPos = ServoResetPos; ServoPos >= 10; ServoPos--)  {
        ourServo.write(ServoPos);
        delay(ServoSpeed);
    }
}

void Robot::AuswurfL()     {
    move.Stop(0);
ourServo.write(ServoResetPos);
    for (ServoPos = ServoResetPos; ServoPos <= 170; ServoPos++)  {
        ourServo.write(ServoPos);
        delay(ServoSpeed);  // durch den delay und allgemein durch die for schleife kann man die Geschwindigkeit des Servos regulieren
    }
}

void Robot::computeCoordinates(){
    
}