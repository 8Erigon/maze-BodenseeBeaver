#include "Movement.h"

Movement::Movement(Motor &motor, sensors_event_t &gyro): motors(&motor){ //Benutzt "Member Initializer List"-Technik ("motors = &motor")
    orientation = &gyro;
}

void Movement::process(){
    offGoal = goalAngle - orientation->orientation.heading;

    if(!manuellSteering){
        short sideSpeed = goalAngle * turnSpeed;
        motors[0].speed = sideSpeed; 
        motors[1].speed = sideSpeed;
        motors[2].speed = -sideSpeed;
        motors[3].speed = -sideSpeed;
        if(abs(goalAngle) <= 5){ //Falls ungefähr richtige Richtung => fahre vorwährts
            motors[0].speed += speed; 
            motors[1].speed += speed;
            motors[2].speed += speed;
            motors[3].speed += speed;
        }
        for(int i = 0;i<4; i++){
            motors[i].processOutput();
        }
    }
}
