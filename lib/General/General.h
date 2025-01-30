#ifndef General_h
#define General_h

//Defines & Enums
#include "DefineEnum.h"
//Display
#include "ILI9341_t3n.h"
//Expander
#include "TCA9534.h"
//Motors
#include "Motor.h"
#include "Movement.h"
//BNO
#include <Adafruit_BNO055.h>
//TOF
#include "TOF.h"
//LED
#include "Adafruit_Neopixel.h"
//Servo
#include "Servo.h"
//Colorsensor
#include "ColorSensor.h"
//Camera
#include "Camera.h"

class Robot{
    public:
    /*
    @details x coordinate of the robot
    */
    int x;
    /*
    @details y coordinate of the robot
    */
    int y; //cooordinates aren't used yet (& probably never)

    static String shortenNumber(long number, uint8_t digits);
    static String setNumberLenght(long number, uint8_t digits);
    static String createScrollingString(String text, uint8_t lenght, uint deltaTime, uint8_t *lastPosition, uint8_t scrollPerSecond, uint8_t maxScrollPerFrame = 255, FillString fillString = right);

    Motor motors[4];
    Movement move; //Movement libary

    TOFonMux TOF[8]; //Time of flight sensors on the mux

    CAMERA leftCamera;
    CAMERA rightCamera;

    ILI9341_t3n display = ILI9341_t3n(7, 8);

    Adafruit_BNO055 bno = Adafruit_BNO055(55, BNO_ADDR, &Wire); //Compass
    sensors_vec_t &orientation = BNOorientation.orientation;
    sensors_vec_t &acceleration = BNOacceleration.acceleration;

    ColorSensorOnMux colorSensor;

    Adafruit_NeoPixel led = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
    void setLedColor(uint32_t color);  

    void processExpanderInputs();
    bool readSwitch(Switch sw);
    bool readButton(Buttons button);
    /*
    @return Returns time in microsseconds since last calling process()/computeDeltaTime()
    */
    long getDeltaTime(){return deltaTime;};
    /*
    @brief Processes everything. Should be used at the start of each loop even when robot is paused
    */
    void process();
    /*
    @brief Function to pause the robot
    @param isRunning true = Robot will run & move; false = Robot is paused
    */
    void setRunning(bool isRunning);

    Servo ourServo;
    void AuswurfR();
    void AuswurfL();
    void ServoPosReset();

    ~Robot(){ //Destructor of the class
        
    };
    Robot();

/*
    Should be private but is public for testing (& because of the dogs main.cpp being implemented)
*/
    bool getExpanderBit(Mutliplexer expander, uint8_t bit);
    TCA9534 topExpander1;
    TCA9534 topExpander2;
    TCA9534 bottomExpander1;
    TCA9534 bottomExpander2;
    TCA9534 motorExpander;
    uint8_t topExpander1Bits;
    uint8_t topExpander2Bits;
    uint8_t bottomExpander1Bits;
    uint8_t bottomExpander2Bits;

    QWIICMUX muxFront;
    QWIICMUX muxBack;

    private:

    sensors_event_t BNOorientation; //to process "bno.getEvent(&bnoData, Adafruit_BNO055::VECTOR_EULER)"
    sensors_event_t BNOacceleration; //to process "bno.getEvent(&bnoData, Adafruit_BNO055::VECTOR_LINEARACCEL)"

    int ServoPosMid = 90;
    int ServoPosRight = 151;
    int ServoPosLeft = 30;
    int ServoPos = 0;

    /*
    @details Time since last using this function
    */
    long computeDeltaTime();
    long lastMicros;
    long deltaTime;
    void computeCoordinates();
};

#endif