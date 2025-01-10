#include <Arduino.h>
#include "../lib/General/General.h"
#include "../lib/MatrixVector/vektors.h"


float RoboHeading = 0;
float RoboHeadingNew = 0;
float RoboHeadingFinal = 0;

int step = 0;

int main()
{
  Serial.begin(9600);
  Serial.println("Hello World");
  Robot robo = Robot();
  // Motor motors[4] ;

  robo.setRunning(false);
  RoboHeading = 0;
    RoboHeadingNew = 0;
    RoboHeadingFinal = 0;

  while (true)
  {
    robo.process();
    Serial.println(robo.orientation.heading);
    Serial.println(robo.orientation.pitch);
    Serial.println(robo.orientation.roll);
    Serial.println();
    //robo.display.println(robo.TOF[TOF_FRONTRIGHT].range);
    // robo.move.TurnRight(20);
    // robo.move.TurnLeft(20);
    // robo.move.ForwardOneTile(15);
    switch(step){
      case 0:
      if(robo.readSwitch(StartSwitch)){
        Serial.println("step 0 complte");
        Serial.println(RoboHeadingNew);
        Serial.println(RoboHeadingFinal);
        step =1;
        break;
      }else{
        step=0;
        robo.setLedColor(GREEN);
        break;
      }

      case 1:
      robo.move.ForwardOneTile(20);
      robo.move.Stop(1000);
      robo.setLedColor(RED);
      Serial.println("step 1 complte");
      step =2;
      break;

      case 2:
      robo.process();
      RoboHeading = robo.orientation.roll;
      RoboHeadingNew = robo.orientation.roll;
      RoboHeadingFinal = RoboHeading + 90;
      if(RoboHeadingFinal > 360){
        RoboHeadingFinal = RoboHeadingFinal - 360;
      }
      step = 3;
      Serial.println("step 2 complte");
      break;

      case 3:
      RoboHeadingNew = robo.orientation.roll;
      robo.move.TurnRight(7);
      if(RoboHeadingFinal >= 90){
      if(RoboHeadingNew >= RoboHeadingFinal){
        step = 4;
        Serial.println("step 3 complte");
        break;
      }else{
        step = 3;
        Serial.println(RoboHeading);
        Serial.println(RoboHeadingFinal);
        delay(1);
        break;
      }
      }else{
        if(RoboHeadingNew >= RoboHeadingFinal && RoboHeadingNew < 180){
          step = 4;
          Serial.println("step 3 complte");
          break;
        }else{
          step = 3;
          Serial.println(RoboHeading);
          delay(1);
          break;
        }
      }
      Serial.println(RoboHeading);
      delay(10);
      break;

      case 4: 
      robo.move.Stop(1);
      step = 0;
      Serial.println("step 4 complte");
      break;


    
      
    }
 }   
}


// put function definitions here:
