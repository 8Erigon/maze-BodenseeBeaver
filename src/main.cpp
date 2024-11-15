#include <Arduino.h>
#include "../lib/General/General.h"
#include "../lib/MatrixVector/vektors.h"
// put function declarations here:

int main(){
  Robot robo;
  robo.move.speed = 10;
  robo.move.goalAngle = 180;
  while(true){
    if(robo.readSwitch(SWITCH9)){
      robo.setRunning(true);
      robo.process();
      Serial.println("Switch 9 On");
    } else {
      robo.setRunning(false);
      Serial.println("Switch 9 Off");
    }
  }
}
// put function definitions here:
