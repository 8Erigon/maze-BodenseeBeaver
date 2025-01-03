#include <Arduino.h>
#include "../lib/General/General.h"
#include "../lib/MatrixVector/vektors.h"
// #include "../Movement/Movement.h"
//  put function declarations here:
#define Speed 15

uint32_t color = 0;
int main()
{
  Serial.begin(9600);
  Serial.println("---Begin programm---");
  Robot robo = Robot();
  Serial.println("---Robo initialized---");

  robo.setRunning(false);
  robo.setLedColor(OFF);

  while (true){
    //robo.process();
    robo.TOF[TOF_LEFTBACK].range = robo.TOF[TOF_LEFTBACK].readRange();
    Serial.println(robo.TOF[TOF_LEFTBACK].range);
    delay(100);
  }
}

// put function definitions here:
