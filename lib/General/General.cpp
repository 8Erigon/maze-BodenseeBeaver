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
    colorSensor.getRGB();
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
//    bottomExpander2.setDeviceAddress(0x24);

    Serial.println("config");
    topExpander1.config(TCA9534::Config::IN);
    topExpander2.config(TCA9534::Config::IN);
    topExpander2.config(5, TCA9534::Config::OUT); //Display Light
    topExpander2.config(4, TCA9534::Config::OUT); //Bluetooth
    Serial.println("config bottom");
    bottomExpander1.config(TCA9534::Config::OUT);
    bottomExpander1.config(0, TCA9534::Config::IN); //AUX_SW1
    bottomExpander1.config(1, TCA9534::Config::IN); //AUX_SW2
//    bottomExpander2.config(TCA9534::Config::OUT);

    Serial.println("polarity");
    topExpander1.polarity(TCA9534::Polarity::ORIGINAL);
    topExpander2.polarity(TCA9534::Polarity::ORIGINAL);
//    bottomExpander1.polarity(TCA9534::Polarity::ORIGINAL);
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
    ourServo.attach(22); 

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

    //Colorsensor
    Serial.println("ColorSensor begin");
    colorSensor = ColorSensorOnMux(0, muxFront, Wire1);
    colorSensor.setInterrupt(false);
}


/*
@details Shortens a number to a certain number of digits and adds the sientific notation
@param number Number to shorten
@param digits Lenght of the output String
@return String of the number 
*/
String Robot::shortenNumber(long number, uint8_t digits){
    String numberString = String(number);
    uint8_t leftDigits = numberString.length() - digits; //Number of digits to cut of
    String leftDigitsString = String(leftDigits); //String

    uint8_t digitsCut = max(0, digits - numberString.length()); //Number of Digits that were cut off (min value = 0)
    String digitsCutString = String(digitsCutString); //String

    uint8_t outputLenght = leftDigits + (digitsCut ? 1 + digitsCutString.length() : 0); //Lenght of output String

    while(outputLenght > digits){ //Check if outputLenght isn't to long
        leftDigits -= outputLenght - digits; //Decreases leftDigits by the amout there where to much digits
        digitsCut += outputLenght - digits; //Increases digitsCut by the amout there where to much digits
        String digitsCutString = String(digitsCutString);
        outputLenght = leftDigits + 1 + digitsCutString.length(); //Re-Calculates variable again 

        if(leftDigits < 1){
            return ""; /* There must be a number left */
        }
    }

    numberString = numberString.substring(0, digits);
    if(digitsCut > 0){
        numberString.append("E" + digitsCutString); //Add sientific notation
    }
    return numberString;
}

String Robot::setNumberLenght(long number, uint8_t digits){
    String numberString = String(number);
    int8_t difference = numberString.length() - digits; //Difference between numberString and digits
    if(difference > 0){ //If numberString is to long
        numberString = Robot::shortenNumber(number, digits);
        if(numberString.length() == digits){ //check if shortenNumber() successed
            return numberString;
        }
    }
    //If numberString is to short
    for(int i = 0; i < abs(difference); i++){
        numberString = "0" + numberString; //add "0" to match the right lenght
    }
    return numberString;
    
}

/*
@details Creates a scrolling String (for if you need to display a to large text)
@param text String to scroll
@param lenght Lenght of the output String
@param deltaTime Time passed since last use of this function (in microsec)
@param *lastPosition Variable for saving last position of the scroll
@param scrollPerSecond How many characters should be scrolled per second
@param maxScrollPerFrame Maximum number of characters that can be scrolled per frame (if deltaTime got to high)
@param fillString Fill the String with spaces if it's to short
@return Current text/String part
*/
String Robot::createScrollingString(String text, uint8_t lenght, uint deltaTime, uint8_t *lastPosition, uint8_t scrollPerSecond, uint8_t maxScrollPerFrame, FillString fillString){
    String output = text;
    if(text.length() < lenght){ //Check if text is to short for scroll
        if(fillString == none){
            return text;
        }
        uint8_t difference = lenght - text.length();
        if(fillString == left){
            for(int i = 0; i < difference; i++){
                output = " " + output;
            }
        }
        if(fillString == right){
            for(int i = 0; i < difference; i++){
                output = output + " ";
            }
        }
        if(fillString == both){
            for(int i = 0; i < difference; i++){
                output = (i%2) ? (output + " ") : (" " + output); //Fill string right and left until lenght is met
            }
        }
        return output;
    }
    uint8_t move = scrollPerSecond * (deltaTime / 1000); //How many characters should be scrolled
    move = min(move, maxScrollPerFrame); //Check if move is to high
    uint8_t leftBorder = *lastPosition + move; //Left border of the scrolling String
    if(leftBorder >= text.length()){ //Check if leftBorder is out of bounce
        leftBorder -= text.length();
    }
    *lastPosition = leftBorder; //Save last position
    uint8_t rightBorder = leftBorder + lenght; //Right border of the scrolling String

    if(rightBorder >= text.length()){ //Check if leftBorder is out of bounce
        rightBorder -= text.length();
        if(rightBorder < leftBorder){ //Check if rightBorder is left from leftBorder
            output = text.substring(leftBorder) + text.substring(0, rightBorder); //Get the scrolling String
        }
    } else{
    output = text.substring(leftBorder, rightBorder); //Get the scrolling String
    }

    return output;
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
    setLedColor(WRGB::RED);
    ourServo.write(ServoPosMid);
    delay(250);
    ourServo.write(ServoPosMid + 5);
    delay(250);
    ourServo.write(ServoPosMid - 5);
    delay(250);
    ourServo.write(ServoPosMid);
    delay(250);
    
    for (ServoPos = ServoPosMid; ServoPos <= ServoPosRight; ServoPos++)  {
        ourServo.write(ServoPos);
        delay(10);
    }
    delay(500);
    ourServo.write(ServoPosRight + 5);
    delay(250);
    ourServo.write(ServoPosRight - 5);
    delay(250);
    ourServo.write(ServoPosRight);
    delay(250);
    setLedColor(WRGB::NONE);
}

void Robot::AuswurfL()     {
    move.Stop(0);
    setLedColor(WRGB::RED);
    ourServo.write(ServoPosMid);
    delay(250);
    ourServo.write(ServoPosMid + 5);
    delay(250);
    ourServo.write(ServoPosMid - 5);
    delay(250);
    ourServo.write(ServoPosMid);
    delay(250);

    for (ServoPos = ServoPosMid; ServoPos >= ServoPosLeft; ServoPos--)  {
        ourServo.write(ServoPos);
        delay(10);
    }
    delay(500);
    ourServo.write(ServoPosLeft - 5);
    delay(250);
    ourServo.write(ServoPosLeft + 5);
    delay(250);
    ourServo.write(ServoPosLeft);
    delay(250);
    setLedColor(WRGB::NONE);
}

void Robot::ServoPosReset()  {
    ourServo.write(ServoPosMid);
}

void Robot::computeCoordinates(){
    
}