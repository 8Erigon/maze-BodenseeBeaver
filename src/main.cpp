#include <Arduino.h>
#include "../lib/General/General.h"
#include "../lib/MatrixVector/vektors.h"
// put function declarations here:
Robot robo;

void setup() {
  // put your setup code here, to run once:
  robo.move.speed = 10;
  robo.move.goalAngle = 180;
}

void loop() {
  // put your main code here, to run repeatedly:
  if(robo.readSwitch(StartSwitch)){
    robo.process();
    Serial.println("Start Switch On");
  } else {
    robo.setRunning(false);
  }
}

// put function definitions here:
