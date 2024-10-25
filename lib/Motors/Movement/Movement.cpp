#include "Movement.h"

Movement::Movement(Motor &_motor): motors(&_motor){ //Benutzt "Member Initializer List"-Technik

}

void Movement::forward(int speed){
    for(int i; i<4; i++){
        motors[i].speed = speed;
    }
}