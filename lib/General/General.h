#ifndef General_h
#define General_h

//Defines & Enums
#include "DefineEnum.h"
//Display
#include <ILI9341_t3n.h>
//Expander
#include <TCA9534.h>
//Motors
#include "../Motors/Motor/Motor.h"
#include "../Motors/Movement/Movement.h"
//BNO
#include <Adafruit_BNO055.h>
//TOF
#include "../TOF/TOF.h"
//LED
#include <Adafruit_NeoPixel.h>
//Servo
#include <Servo.h>

class Robot{
    public:
    /*
    @details x coordinate of the robot
    */
    int x;
    /*
    @details y coordinate of the robot
    */
    int y;

    Motor motors[4];
    Movement move;

    TOFonMux TOF[8];

    ILI9341_t3n display = ILI9341_t3n(7, 8);

    Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28, &Wire);
    sensors_vec_t &orientation = BNOorientation.orientation;
    sensors_vec_t &acceleration = BNOacceleration.acceleration;

    Adafruit_NeoPixel led = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
    void setLedColor(uint32_t color);  

    void processExpanderInputs();
    bool readSwitch(Switch sw);
    bool readButton(Buttons button);
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

    Servo myservo;
    int ServoSpeed = 15;
    void AuswurfR();
    void AuswurfL();

    ~Robot(){ //Destructor of the class
        
    };
    Robot();

    private:

    long lastMicros;
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

    sensors_event_t BNOorientation; //to process "bno.getEvent(&bnoData, Adafruit_BNO055::VECTOR_EULER)"
    sensors_event_t BNOacceleration; //to process "bno.getEvent(&bnoData, Adafruit_BNO055::VECTOR_LINEARACCEL)"

    bool getExpanderBit(Mutliplexer expander, uint8_t bit);

    int ServoPos = 0;
    int ServoResetPos = 90;

    /*
    @details Time since last using this function
    */
    long computeDeltaTime();
    long deltaTime;
    void computeCoordinates();
};

#endif