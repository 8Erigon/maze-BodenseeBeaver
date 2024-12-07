#ifndef General_h
#define General_h

//Defines & Enums
#include "DefineEnum.h"
//Display
#include <Adafruit_ILI9341.h>
//Expander
#include <TCA9534.h>
//Motors
#include "../Motors/Motor/Motor.h"
#include "../Motors/Movement/Movement.h"
//BNO
#include <Adafruit_BNO055.h>
//TOF
#include "../TOF/TOF.h"

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

    Adafruit_ILI9341 display = Adafruit_ILI9341(7, 8);

    Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28, &Wire);
    sensors_event_t orientation; //to process "bno.getEvent(&bnoData, Adafruit_BNO055::VECTOR_EULER)"
    sensors_event_t acceleration; //to process "bno.getEvent(&bnoData, Adafruit_BNO055::VECTOR_LINEARACCEL)"

    void processExpanderInputs();
    bool readSwitch(Switch sw);
    bool readButton(Buttons button);
    long deltaTime;
    /*
    @brief Processes everything. Should be used at the start of each loop even when robot is paused
    */
    void process();
    /*
    @brief Function to pause the robot
    @param isRunning true = Robot will run & move; false = Robot is paused
    */
    void setRunning(bool isRunning);

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

    bool getExpanderBit(Mutliplexer expander, uint8_t bit);
    /*
    @details Time since last using this function
    */
    long computeDeltaTime();
    void computeCoordinates();
};

#endif