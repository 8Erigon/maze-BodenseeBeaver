#include <Arduino.h>
#include "Kit Auswerfer.h"
#include <Servo.h>

Servo myservo;

int ServoPos = 0;
int ServoResetPos = 90;
int ServoSpeed = 15;


void AuswurfR()     {
    myservo.write(ServoResetPos);
    for (ServoPos = ServoResetPos; ServoPos >= 10; ServoPos--)  {
        myservo.write(ServoPos);
        delay(ServoSpeed);
    }
}

void AuswurfL()     {
    myservo.write(ServoResetPos);
    for (ServoPos = ServoResetPos; ServoPos >= 170; ServoPos++)  {
        myservo.write(ServoPos);
        delay(ServoSpeed);
    }
}

void setupServo()    {
    myservo.attach(9);      // hier muss man noch den Port anpassen, 9 kommt nur aus dem Beispielprogramm
}