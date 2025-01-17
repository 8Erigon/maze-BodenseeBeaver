#include "timer.h"

// Variables for cycle time measurement
static unsigned long cycleTimeMemory = 0;         // Unit ; µs : 0µs
static unsigned long cycleTimeMinimum = 1000000;  // Unit ; µs : 1s
static unsigned long cycleTimeCurrent = 0;        // Unit ; µs : 0s
static unsigned long cycleTimeMaximum = 0;        // Unit ; µs : 0s
static unsigned long MeasTimeMemory = 0;          // Unit ; µs : 0s
unsigned long cycleTime = 0;                      // Unit ; µs : 0µs
unsigned long MeasTime = 0;                       // Unit ; µs : 0µs

//Varables for timer functions
unsigned long timerMemory[TIMERMAX];  // Unit ; µs :
bool timerFlag[TIMERMAX];

bool timerFunction(int type, int timerNumber, bool inputSignal, unsigned long delayTime) {
  bool timerOutput = LOW;
  // check timer number range 0 to TIMERMAX
  if (timerNumber >= 0 && timerNumber <= TIMERMAX) {
    switch (type) {
      case TON:  // TON
        if (inputSignal == LOW) {
          timerMemory[timerNumber] = micros();
          timerOutput = LOW;
        } else {
          if (micros() >= timerMemory[timerNumber] + delayTime) {
            timerOutput = HIGH;
          } else {
            timerOutput = LOW;
          }
        }
        break;

      case TOFF:  // TOFF
        if (inputSignal == HIGH) {
          timerMemory[timerNumber] = micros();
          timerOutput = HIGH;
        } else {
          if (micros() >= timerMemory[timerNumber] + delayTime) {
            timerOutput = LOW;
          } else {
            timerOutput = HIGH;
          }
        }
        break;

      case TFLASH:  // TFLASH
        if (inputSignal == LOW) {
          timerMemory[timerNumber] = micros();
          timerFlag[timerNumber] = LOW;
          timerOutput = LOW;
        } else {
          if (timerFlag[timerNumber] == LOW) {  // output HIGH
            if (micros() >= timerMemory[timerNumber] + delayTime) {
              timerFlag[timerNumber] = HIGH;
              timerMemory[timerNumber] = timerMemory[timerNumber] + delayTime;
              timerOutput = LOW;
            } else {
              timerOutput = HIGH;
            }
          } else {  // output LOW
            if (micros() >= timerMemory[timerNumber] + delayTime) {
              timerFlag[timerNumber] = LOW;
              timerMemory[timerNumber] = timerMemory[timerNumber] + delayTime;
              timerOutput = HIGH;
            } else {
              timerOutput = LOW;
            }
          }
        }
        break;

      case TCLOCK:  // TCLOCK
        if (inputSignal == LOW) {
          timerMemory[timerNumber] = micros();
          timerFlag[timerNumber] = LOW;
          timerOutput = LOW;
        } else {
          if (timerFlag[timerNumber] == LOW) {  // first clock impuls
            timerFlag[timerNumber] = HIGH;
            timerOutput = HIGH;
          } else {  // following clock impuls
            if (micros() >= timerMemory[timerNumber] + delayTime) {
              timerMemory[timerNumber] = timerMemory[timerNumber] + delayTime;
              timerOutput = HIGH;
            } else {
              timerOutput = LOW;
            }
          }
        }
        break;

      case TIMPULS:  // TIMPULS
        if (inputSignal == HIGH && timerFlag[timerNumber] == LOW) {
          timerFlag[timerNumber] = HIGH;
        }
        if (inputSignal == LOW && timerFlag[timerNumber] == LOW) {
          timerMemory[timerNumber] = micros();
        }
        if (timerFlag[timerNumber] == HIGH) {
          if (micros() >= timerMemory[timerNumber] + delayTime) {
            timerOutput = LOW;
            timerFlag[timerNumber] = LOW;
          } else {
            timerOutput = HIGH;
          }
        }
        break;

      default:  // if timer type is invalid
        timerOutput = LOW;
        break;
    }
  } else {  // if timer number is invalid
    timerOutput = LOW;
  }
  return (timerOutput);
}


// Cycle Time Measurement
// 1.2.2024
// parameters:
// mode  :
//   RESETTIME   : input signal, reset memory of Cycle Time Measurement; µs
//   READMIN     : input signal, read Cycle Time Measurement Minimum; µs
//   READCUR     : input signal, read Cycle Time Measurement Current; µs
//   READMAX     : input signa,l read Cycle Time Measurement Maximim; µs
//
// Declaration for cycle time measurement
// #define RESETTIME 0    // reset memory of Cycle Time Measurement; µs
// #define READMIN 1      // read Cycle Time Measurement Minimum; µs
// #define READCUR 2      // read Cycle Time Measurement Current; µs
// #define READMAX 3      // read Cycle Time Measurement Maximim; µs
//
// Test: Current cycle time
// cycleTime = cycleTimeMeasurement (CT_READCUR);

unsigned long cycleTimeMeasurement(int mode) {
  unsigned long timeDifferenz = 0;
  unsigned long cycleTimeDisplay = 0;
  // READ-Function
  timeDifferenz = micros() - cycleTimeMemory;
  if (cycleTimeMinimum > timeDifferenz) cycleTimeMinimum = timeDifferenz;
  cycleTimeCurrent = timeDifferenz;
  if (cycleTimeMaximum < timeDifferenz) cycleTimeMaximum = timeDifferenz;
  cycleTimeMemory = micros();

  switch (mode) {
      // RESET-Function
    case RESETTIME:                // RESET
      cycleTimeMinimum = 1000000;  // 1s
      cycleTimeCurrent = 0;        // 0s
      cycleTimeMaximum = 0;        // 0s
      cycleTimeDisplay = 0;        // 0s
      break;
      // Display Minimum
    case READMIN:  // Minimum
      cycleTimeDisplay = cycleTimeMinimum;
      break;
      // Display Current
    case READCUR:  // Minimum
      cycleTimeDisplay = cycleTimeCurrent;
      break;
      // Display Maximum
    case READMAX:  // Minimum
      cycleTimeDisplay = cycleTimeMaximum;
      break;
    default:  // if mode is invalid
      cycleTimeDisplay = cycleTimeCurrent;
      break;
  }
  return (cycleTimeDisplay);
}




// Time Measurement
// 1.2.2024
// parameters:
// mode  :
//   RESETTIME   : input signal, reset memory of Time Measurement; µs
//   READCUR     : input signal, read Time Measurement Current; µs
//
// Declaration for time measurement
// #define RESETTIME 0    // reset memory of Time Measurement; µs
// #define READCUR 2      // read Time Measurement Current; µs
//
// Test: Current time
// MeasTime = TimeMeasurement (RESETTIME);
// MeasTime = TimeMeasurement (READCUR);

unsigned long timeMeasurement(int mode) {
  unsigned long timeDifferenz = 0;
  switch (mode) {
      // RESET-Function
    case RESETTIME:  // RESET
      MeasTimeMemory = micros();
      timeDifferenz = 0;  // 0s
      break;
      // Display Current time
    case READCUR:  // Read
      timeDifferenz = micros() - MeasTimeMemory;
      break;
    default:  // if mode is invalid
      timeDifferenz = 99999;
      break;
  }
  return (timeDifferenz);
}

