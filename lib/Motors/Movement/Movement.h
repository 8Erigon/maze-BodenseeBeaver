#ifndef Movement_h
#define Movement_h

#include "../Motor/Motor.h"
#include "../TCA9534-master/TCA9534.h"


class Movement
{
public:
    /*
    @param &_motor first element in a array of 4 motors 
    @example Motor motors[4]; Movement move(motors[0]);
    */
    Movement(Motor &_motor);

    /*
    @brief Pointer to array of 4 motors. Just handle it like a normal array.
    @example motor[0].speed = 0;
    */
    Motor* motor;
};

#endif