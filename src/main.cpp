#include <Arduino.h>
#include "../lib/General/General.h"
#include "../lib/MatrixVector/vektors.h"
// put function declarations here:

int main(){
  Robot robo;
  robo.move.speed = 10;
  robo.move.goalAngle = 180;
  while(true){
    if(robo.readSwitch(SWITCH10)){
      robo.setRunning(true);
      Serial.println("Switch On");
    } else {
      robo.setRunning(false);
      Serial.println("Switch Off");
    }
    robo.process();
  }
}
// put function definitions here:
