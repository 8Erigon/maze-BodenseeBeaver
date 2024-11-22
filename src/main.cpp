#include <Arduino.h>
#include "../lib/General/General.h"
#include "../lib/MatrixVector/vektors.h"
// put function declarations here:

int main(){
  Robot robo;
  robo.move.speed = 10;
  robo.move.goalAngle = 0;
  robo.setRunning(true);
  while(true){
    if(robo.readSwitch(SWITCH10)){
      for(int i = 0;i < 4; i++){
      robo.motors[i].speed = 50;
      }
      Serial.println("Switch On");
    } 
    else {
      for(int i = 0;i < 4; i++){
      robo.motors[i].speed = 0;
      }
      Serial.println("Switch Off");
    }

    for(int i = 0; i <4; i++){
      robo.motors[i].processOutput();
    }
    robo.process();
    delay(1000);
  }
}
// put function definitions here:
