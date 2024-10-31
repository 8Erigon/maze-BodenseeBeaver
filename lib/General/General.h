#ifndef General_h
#define General_h

//Display
#include "../Display/Adafruit_ILI9341-master/Adafruit_ILI9341.h"

//Expander
#include "../Motors/TCA9534-master/TCA9534.h"
//Motors
#include "../Motors/Movement/Movement.h"

#define MOTOR_FREQUENCY 150

#define MOTOR_BACK_LEFT_IN1 2
#define MOTOR_BACK_LEFT_IN2 3
#define MOTOR_BACK_LEFT_PWM 5

#define MOTOR_BACK_RIGHT_IN1 0
#define MOTOR_BACK_RIGHT_IN2 1
#define MOTOR_BACK_RIGHT_PWM 4

#define MOTOR_FRONT_LEFT_IN1 4
#define MOTOR_FRONT_LEFT_IN2 5
#define MOTOR_FRONT_LEFT_PWM 6

#define MOTOR_FRONT_RIGHT_IN1 6
#define MOTOR_FRONT_RIGHT_IN2 7
#define MOTOR_FRONT_RIGHT_PWM 9
//BNO
#include "../Adafruit_BNO055/Adafruit_BNO055.h"

//------------------

enum Buttons
{
    BUTTON1 = 1,
    BUTTON2 = 2,
    BUTTON3 = 3,
    BUTTON4 = 4,
    BUTTON5 = 5,
    BUTTON6 = 6
};
enum Switch{
    Switch9 = 9,
    Switch10 = 10,
    Switch11 = 11,
    Switch12 = 12,
    StartSwitch
};

enum Mutliplexer{
    MULTIPLEXER_TOP_1,
    MULTIPLEXER_TOP_2,
    MULTIPLEXER_BOTTOM_1,
    MULTIPLEXER_BOTTOM_2,
};

enum SkyDirection{
    North,
    East,
    South,
    West
};

class Robot{
    public:
    bool init();
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

    Adafruit_ILI9341 Display = Adafruit_ILI9341(7, 8);

    Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28, &Wire);
    sensors_event_t orientation; //to process "bno.getEvent(&orientation, Adafruit_BNO055::VECTOR_EULER)"
    sensors_event_t acceleration; //to process "bno.getEvent(&acceleration, Adafruit_BNO055::VECTOR_LINEARACCEL)"

    void processExpanderInputs();
    bool readSwitch(Switch sw);
    bool readButton(Buttons button);
    long deltaTime;
    /*
    @details Processes everything. Should be used at the start of each loop even when robot is paused
    */
    void process();
    /*
    @details Function to pause the robot
    @param isRunning true == Robot will run & move; false == Robot is paused
    */
    void setRunning(bool isRunning);

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