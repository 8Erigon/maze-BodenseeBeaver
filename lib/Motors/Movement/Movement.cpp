#include "Movement.h"

Movement::Movement(Motor &_motor, sensors_event_t &gyro): motors(&_motor){ //Benutzt "Member Initializer List"-Technik
    orientation = &gyro;
}

void Movement::process(){
    offGoal = goalAngle - orientation->orientation.heading;
    if(!manuellSteering){
        for(int i = 0;i<4; i++){
            motors[i].processOutput();
        }
    }
}
