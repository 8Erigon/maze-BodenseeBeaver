#ifndef General_h
#define General_h

//Display
#include "../Display/Adafruit_ILI9341-master/Adafruit_ILI9341.h"
//Expander
#include "../Motors/TCA9534-master/TCA9534.h"
//Motors
#include "../Motors/Motor/Motor.h"
#include "../Motors/Movement/Movement.h"

#define MOTOR_FREQUENCY 150

#define MOTOR_BACK_LEFT_IN1 2
#define MOTOR_BACK_LEFT_IN2 3
#define MOTOR_BACK_LEFT_PWM 5
#define MOTOR_BACK_LEFT_FACTOR -0.5

#define MOTOR_BACK_RIGHT_IN1 0
#define MOTOR_BACK_RIGHT_IN2 1
#define MOTOR_BACK_RIGHT_PWM 4
#define MOTOR_BACK_RIGHT_FACTOR 1

#define MOTOR_FRONT_LEFT_IN1 4
#define MOTOR_FRONT_LEFT_IN2 5
#define MOTOR_FRONT_LEFT_PWM 6
#define MOTOR_FRONT_LEFT_FACTOR -1

#define MOTOR_FRONT_RIGHT_IN1 6
#define MOTOR_FRONT_RIGHT_IN2 7
#define MOTOR_FRONT_RIGHT_PWM 9
#define MOTOR_FRONT_RIGHT_FACTOR 1
//BNO
#include "../Adafruit_BNO055/Adafruit_BNO055.h"
//TOF
#include "../Adafruit_VL6180X-master/Adafruit_VL6180X.h"
//------------------

enum Buttons
{
    BUTTON1 = 4,
    BUTTON2 = 5,
    BUTTON3 = 6,
    BUTTON4 = 7,
    BUTTON5 = 8,
    BUTTON6 = 9
};
enum Switch{
    SWITCH9 = 0,
    SWITCH10 = 1,
    SWITCH11 = 2,
    SWITCH12 = 3,
    StartSwitch
};

enum Mutliplexer{
    MULTIPLEXER_TOP_1,
    MULTIPLEXER_TOP_2,
    MULTIPLEXER_BOTTOM_1,
    MULTIPLEXER_BOTTOM_2,
};

enum TOF{
    FRONTRIGHT,
    FRONTLEFT,
    RIGHTFRONT,
    RIGHTBACK,
    LEFTFRONT,
    LEFTBACK,
    BACKRIGHT,
    BACKLEFT
};

enum SkyDirection{
    North,
    East,
    South,
    West
};

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

    Adafruit_VL6180X TOF[8];

    //Adafruit_ILI9341 display = Adafruit_ILI9341(7, 8);

    Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28, &Wire);
    sensors_event_t orientation; //to process "bno.getEvent(&orientation, Adafruit_BNO055::VECTOR_EULER)"
    sensors_event_t acceleration; //to process "bno.getEvent(&acceleration, Adafruit_BNO055::VECTOR_LINEARACCEL)"

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
    bool getExpanderBit(Mutliplexer expander, uint8_t bit);
    /*
    @details Time since last using this function
    */
    long computeDeltaTime();
    void computeCoordinates();
};

#endif