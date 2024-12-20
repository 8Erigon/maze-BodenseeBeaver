#include <Arduino.h>
#include "../lib/General/General.h"
#include "../lib/MatrixVector/vektors.h"
// #include "../Movement/Movement.h"
//  put function declarations here:
#define Speed 15

int main()
{
  Serial.begin(9600);
  Robot robo;
  // Motor motors[4] ;

  robo.setRunning(false);
  while (true)
  {
    robo.process();
    Serial.println(robo.orientation.heading);
    Serial.println(robo.orientation.pitch);
    Serial.println(robo.orientation.roll);
    Serial.println();
    robo.display.println(robo.TOF[TOF_FRONTRIGHT].range);
    // robo.move.TurnRight(20);
    // robo.move.TurnLeft(20);
    // robo.move.ForwardOneTile(15);
    if (robo.readSwitch(StartSwitch))
    {
      float RoboHeading = robo.orientation.roll;
      float RoboHeadingNew = robo.orientation.roll;
      float RoboHeadingFinal = RoboHeading + 90;

      Serial.println(RoboHeading);

      if (RoboHeadingFinal < 360)
      {

        while (RoboHeadingNew < RoboHeadingFinal)
        {
          robo.process();
          robo.motors[0].speed = Speed;
          robo.motors[1].speed = Speed;
          robo.motors[2].speed = -Speed;
          robo.motors[3].speed = -Speed;
          robo.motors[0].processOutput();
          robo.motors[1].processOutput();
          robo.motors[2].processOutput();
          robo.motors[3].processOutput();
          delay(100);
          robo.move.Stop(10);

          RoboHeadingNew = robo.orientation.roll;
          Serial.println(RoboHeadingNew);
          // delay(TurnDuration/Speed);
        }
      }
      else
      {
        RoboHeadingFinal = RoboHeadingFinal - 360;
        while (RoboHeadingNew > RoboHeadingFinal)
        {
          robo.process();
          robo.motors[0].speed = Speed;
          robo.motors[1].speed = Speed;
          robo.motors[2].speed = -Speed;
          robo.motors[3].speed = -Speed;
          robo.motors[0].processOutput();
          robo.motors[1].processOutput();
          robo.motors[2].processOutput();
          robo.motors[3].processOutput();
          delay(10);
          robo.move.Stop(1);

          RoboHeadingNew = robo.orientation.roll;
          Serial.println(RoboHeadingNew);
          // delay(TurnDuration/Speed);
        }
      }
      robo.move.Stop(200);
    }
    // robo.move.TurnRight(10);
    // motors[0].speed = 20;
    // delay(1000);
    robo.move.Stop(1000);
  }
}

// put function definitions here:
