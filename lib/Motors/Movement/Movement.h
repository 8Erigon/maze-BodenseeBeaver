#ifndef Movement_h
#define Movement_h

#include "../Motor/Motor.h"
#include "../TCA9534-master/TCA9534.h"


class Movement
{
public:
    Movement(Motor& _motor[4]);

    Motor motor[4];
};

#endif