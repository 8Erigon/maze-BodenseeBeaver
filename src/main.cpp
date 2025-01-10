#include <Arduino.h>
#include "../lib/General/General.h"
#include "../lib/MatrixVector/vektors.h"
// #include "../Movement/Movement.h"
//  put function declarations here:
#define Speed 15

/*
#define VL6180X_ERROR_NONE 0        ///< Success!
#define VL6180X_ERROR_SYSERR_1 1    ///< System error
#define VL6180X_ERROR_SYSERR_5 5    ///< Sysem error
#define VL6180X_ERROR_ECEFAIL 6     ///< Early convergence estimate fail
#define VL6180X_ERROR_NOCONVERGE 7  ///< No target detected
#define VL6180X_ERROR_RANGEIGNORE 8 ///< Ignore threshold check failed
#define VL6180X_ERROR_SNR 11        ///< Ambient conditions too high
#define VL6180X_ERROR_RAWUFLOW 12   ///< Raw range algo underflow
#define VL6180X_ERROR_RAWOFLOW 13   ///< Raw range algo overflow
#define VL6180X_ERROR_RANGEUFLOW 14 ///< Raw range algo underflow
#define VL6180X_ERROR_RANGEOFLOW 15 ///< Raw range algo overflow
*/

uint32_t color = 0;
TOF_POSITION testTOF = TOF_LEFTBACK;
int main()
{
  Serial.begin(9600);
  Serial.println("---Begin programm---");
  Robot robo = Robot();
  Serial.println("---Robo initialized---");

  robo.setRunning(false);
  robo.setLedColor(OFF);

  while (true){
    robo.process();

    Serial.print("TOF ");
    Serial.print(testTOF);
    Serial.print(":");

    robo.TOF[testTOF].range = robo.TOF[testTOF].readRange();
    Serial.print("read ");
    Serial.print(robo.TOF[testTOF].range);
    bool status = robo.TOF[testTOF].readRangeStatus();
    Serial.print(" status ");
    Serial.println(status);

    delay(200);
  }
}

// put function definitions here:
