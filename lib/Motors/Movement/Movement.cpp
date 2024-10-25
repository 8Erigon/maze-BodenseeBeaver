#include "Movement.h"

Movement::Movement(Motor &_motor, sensors_event_t &gyro): motors(&_motor){ //Benutzt "Member Initializer List"-Technik
    rotation = &gyro;
}

void Movement::forward(int speed){
    for(int i = 0; i<4; i++){
        motors[i].speed = speed;
    }
}

