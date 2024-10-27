#ifndef Movement_h
#define Movement_h

#include "../Motor/Motor.h"
#include "../TCA9534-master/TCA9534.h"
#include <Adafruit_BNO055.h>

class Movement
{
public:
    /*
    @param &_motor first element in a array of 4 motors 
    @param &gyro variable that holds the orientation data of a BNO
    @example Motor motors[4]; sensors_event_t gyro; Movement move(motors[0], gyro);
    */
    Movement(Motor &_motor, sensors_event_t &gyro);
    /*
    @brief drive the roboter forward or backwards with a speed upto 255
    @param speed from -255 to 255; 
    */
    void forward(int speed);
    /*
    @brief Processes Motors&Movement. Should be used at the start of each loop
    */
    void process();
    /*
    @brief Angle the robot should turn to in the end.
    */
    ushort goalAngle = 0;
private:
    /*
    @brief pointer to a sensor_event_t holding orientation data of a BNO 
    */
    sensors_event_t *rotation;
    /*
    @brief Pointer to array of 4 motors. Just handle it like a normal array.
    @example motor[0].speed = 0;
    */
    Motor* motors;
};

#endif