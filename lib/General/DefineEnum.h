#ifndef DefineEnum_h
#define DefineEnum_h

//Motors
#define MOTOR_FREQUENCY 150

//Mo2 bei Platine
#define MOTOR_BACK_LEFT_IN1 2
#define MOTOR_BACK_LEFT_IN2 3
#define MOTOR_BACK_LEFT_PWM 5
#define MOTOR_BACK_LEFT_FACTOR -1

//Mo4  bei Platine
#define MOTOR_BACK_RIGHT_IN1 6
#define MOTOR_BACK_RIGHT_IN2 7
#define MOTOR_BACK_RIGHT_PWM 9
#define MOTOR_BACK_RIGHT_FACTOR 5

//Mo3 bei Platine
#define MOTOR_FRONT_LEFT_IN1 4
#define MOTOR_FRONT_LEFT_IN2 5
#define MOTOR_FRONT_LEFT_PWM 6
#define MOTOR_FRONT_LEFT_FACTOR -3

//Mo1  bei Platine
#define MOTOR_FRONT_RIGHT_IN1 0
#define MOTOR_FRONT_RIGHT_IN2 1
#define MOTOR_FRONT_RIGHT_PWM 4
#define MOTOR_FRONT_RIGHT_FACTOR 1

//------Enum--------

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

#endif