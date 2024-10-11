#include "Movement.h"

Movement::Movement(Motor* _motor){
    for (int i = 0; i<4; i++){
        *motor[i] = *(_motor + i);
    }
}
