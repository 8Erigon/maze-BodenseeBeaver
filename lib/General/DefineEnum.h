#ifndef DefineEnum_h
#define DefineEnum_h

//Motors
#define MOTOR_FREQUENCY 150

//Mo2 bei Platine
#define MOTOR_FRONT_RIGHT_IN1 2
#define MOTOR_FRONT_RIGHT_IN2 3
#define MOTOR_FRONT_RIGHT_PWM 5
#define MOTOR_FRONT_RIGHT_FACTOR 7

//Mo4  bei Platine
#define MOTOR_FRONT_LEFT_IN1 6                           
#define MOTOR_FRONT_LEFT_IN2 7
#define MOTOR_FRONT_LEFT_PWM 9
#define MOTOR_FRONT_LEFT_FACTOR -8.5

//Mo3 bei Platine
#define MOTOR_BACK_RIGHT_IN1 4
#define MOTOR_BACK_RIGHT_IN2 5
#define MOTOR_BACK_RIGHT_PWM 6
#define MOTOR_BACK_RIGHT_FACTOR 6

//Mo1  bei Platine
#define MOTOR_BACK_LEFT_IN1 0
#define MOTOR_BACK_LEFT_IN2 1
#define MOTOR_BACK_LEFT_PWM 4
#define MOTOR_BACK_LEFT_FACTOR -8

//Mux / Portexpander
#define MUXBACK_ADDR 0x71 //Jumper 0 gelötet
#define MUXFRONT_ADDR 0x70 //Jumper 0 & 1 gelötet

//Led
#define LED_COUNT 8
#define LED_PIN 20

//BNO
#define BNO_ADDR 0x28

//-------Enums---------

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
    TOF_FRONTRIGHT = 0,
    TOF_FRONTLEFT = 1,
    TOF_BACKRIGHT = 2,
    TOF_BACKLEFT = 3,
    TOF_RIGHTFRONT = 4,
    TOF_RIGHTBACK = 5,
    TOF_LEFTFRONT = 6,
    TOF_LEFTBACK = 7
};

enum SkyDirection{
    North,
    East,
    South,
    West
};

enum WRGB {  //uint32_t for colors
    //0x opacity red green blue
    RED = 0x00FF0000,
    GREEN = 0x0000FF00,
    BLUE = 0x000000FF,
    YELLOW = 0x00FFFF00,
    ORANGE = 0x00FFA500,
    CYAN = 0x0000FFFF,
    MAGENTA = 0x00FF00FF,
    WHITE = 0x00FFFFFF,
    OFF = 0xFF000000
};

#endif