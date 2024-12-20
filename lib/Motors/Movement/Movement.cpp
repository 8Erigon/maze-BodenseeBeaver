#include "Movement.h"


Movement::Movement(Motor &motor, sensors_vec_t &orientation, sensors_vec_t &acceleration): motors(&motor){ //Benutzt "Member Initializer List"-Technik ("motors = &motor")
    this->orientation = &orientation;
    this->acceleration = &acceleration;
}

void Movement::process(){
    offGoal = goalAngle - orientation->heading;

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

void Movement::Stop(int  time){
    motors[0].speed = 0;
    motors[1].speed = 0;
    motors[2].speed = 0;
    motors[3].speed = 0;
    motors[0].processOutput();
    motors[1].processOutput();
    motors[2].processOutput();
    motors[3].processOutput();
    delay(time);
}

void Movement::TurnRight(int Speed){
    //-> this bnoData = &bnoData;
    float RoboHeading = orientation->roll;
    float RoboHeadingNew = orientation->roll;
    float RoboHeadingFinal = RoboHeading + 90;
    
    Serial.println(RoboHeading);


    if(RoboHeadingFinal < 360){
        
        while(RoboHeadingNew < RoboHeadingFinal){
            motors[0].speed = Speed;
            motors[1].speed = Speed;
            motors[2].speed = - Speed;
            motors[3].speed = - Speed;
            motors[0].processOutput();
            motors[1].processOutput();
            motors[2].processOutput();
            motors[3].processOutput();
            delay(10);
            Stop(1);
        
            RoboHeadingNew = orientation->roll;
            Serial.println(RoboHeadingNew);
            //delay(TurnDuration/Speed);
        }
    }else{
        RoboHeadingFinal = RoboHeadingFinal - 360;
        while(RoboHeadingNew > RoboHeadingFinal){
            motors[0].speed = Speed;
            motors[1].speed = Speed;
            motors[2].speed = - Speed;
            motors[3].speed = - Speed;
            motors[0].processOutput();
            motors[1].processOutput();
            motors[2].processOutput();
            motors[3].processOutput();
            delay(10);
            Stop(1);

            RoboHeadingNew = orientation->roll;
            Serial.println(RoboHeadingNew);
            //delay(TurnDuration/Speed);
        }
    }
    Stop(200);
}
void Movement::TurnLeft(int Speed){
    motors[0].speed = - Speed;
    motors[1].speed = - Speed;
    motors[2].speed = Speed;
    motors[3].speed = Speed;
    motors[0].processOutput();
    motors[1].processOutput();
    motors[2].processOutput();
    motors[3].processOutput();
    delay(TurnDuration/Speed);
}

void Movement::ForwardOneTile(int speed){
    motors[0].speed = speed;
    motors[1].speed = speed;
    motors[2].speed = speed;
    motors[3].speed = speed;
    
    motors[0].processOutput();
    motors[1].processOutput();
    motors[2].processOutput();
    motors[3].processOutput();
    delay(ForwardDuration/speed);
}


