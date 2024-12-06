#include <Arduino.h>
#include "../lib/General/General.h"
#include "../lib/MatrixVector/vektors.h"
// put function declarations here:

int main(){
  Serial.begin(9600);
  Robot robo;

  robo.setRunning(false);
  while(true){
    robo.process();
    Serial.println(robo.orientation.orientation.heading);
    Serial.println(robo.orientation.orientation.pitch);
    Serial.println(robo.orientation.orientation.roll);
    Serial.println();
    delay(1000);
  }
}
// put function definitions here:
