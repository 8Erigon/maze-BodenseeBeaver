#include "Movement.h"

Movement::Movement(Motor &_motor, sensors_event_t &gyro): motors(&_motor){ //Benutzt "Member Initializer List"-Technik
    orientation = &gyro;
}

void Movement::process(){
    for(int i = 0;i<4; i++){
        motors[i].processOutput();
    }
}
