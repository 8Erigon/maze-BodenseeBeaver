#include "Movement.h"

Movement::Movement(Motor &motor, sensors_event_t &bnoData): motors(&motor){ //Benutzt "Member Initializer List"-Technik ("motors = &motor")
    this->bnoData = &bnoData;
}

void Movement::process(){
    offGoal = goalAngle - bnoData->orientation.heading;

    if(movementControl != manuel){
        short sideSpeed = goalAngle * turnSpeed;
        motors[FrontLeft].speed = sideSpeed; 
        motors[BackLeft].speed = sideSpeed;
        motors[FrontRight].speed = -sideSpeed;
        motors[BackRight].speed = -sideSpeed;
        if(abs(goalAngle) <= offsetTreshhold){ //Falls ungefähr richtige Richtung => fahre vorwährts
            motors[FrontLeft].speed += speed; 
            motors[BackLeft].speed += speed;
            motors[FrontRight].speed += speed;
            motors[BackRight].speed += speed;
        }
        for(int i = 0;i<4; i++){
            motors[i].processOutput();
        }
    }
}
