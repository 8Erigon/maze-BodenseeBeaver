#ifndef Movement_h
#define Movement_h

#include "../Motor/Motor.h"
#include "../TCA9534-master/TCA9534.h"
#include <Adafruit_BNO055.h>
//#include "General.h"

#define TurnDuration 11000
#define ForwardDuration 11000

//Adafruit_BNO055 bno(55);

enum MotorPosition {
    FrontLeft = 0,
    BackLeft = 1,
    FrontRight = 2,
    BackRight = 3
};

enum MovementControl {
    manuel,
    compass,
    TOF
};

class Movement
{
public:
    /*
    @param &motor first element in a array of 4 motors. First 2 elements are left motors. Last 2 are right motors. 
    @param &gyro variable that holds the orientation data of a BNO
    @example Motor motors[4]; sensors_event_t gyro; Movement move(motors[0], gyro);
    */
    Movement(Motor &motor, sensors_event_t &bnoData);
    Movement();

    void TurnRight (int Speed);
    void TurnLeft (int Speed);
    void ForwardOneTile(int speed);
    void Stop(int time);
    /*
    @brief drive the roboter forward or backwards with a speed upto 255
    @param speed from -255 to 255; 
    */
    short speed = 0;
    /*
    @brief Angle the robot should turn to in the end.
    */
    ushort goalAngle = 0;
    #define turnSpeed 2 //Motor speed when turning PER DEGREE to TURN
    #define offsetTreshhold 5 //Degrees the robot can be of of goalAngle and still drive forward
    /*
    @brief degrees the robots of from the goalAngle
    */
    short offGoal;

    /*
    @brief true == turns Movement class doesn't control Motors
    */
    MovementControl movementControl = compass;
    /*
    @brief Processes Motors&Movement. Should be used at the start of each loop
    */
    void process();
private:
    /*
    @brief pointer to a sensor_event_t holding orientation data of a BNO 
    */
    sensors_event_t *bnoData;
    /*
    @brief Pointer to array of 4 motors. Just handle it like a normal array. First 2 elements are left motors. Last 2 are right motors. 
    @example motor[0].speed = 0;
    */
    Motor* motors;
};

#endif