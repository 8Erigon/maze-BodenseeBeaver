#include <Arduino.h>

// Declaration
#define OFF false
#define ON true
// Declaration for timer functions
#define TON 1
#define TOFF 2
#define TFLASH 3
#define TCLOCK 4
#define TIMPULS 5
#define TIMERMAX 10
#define TCHAIN1 0
#define TCHAIN2 1
#define TCHAIN3 2
#define TBUTTONSINGLESTEP 3

//Time declaration
#define MILISEKOND 1000
#define SEKOND 1000*MILISEKOND

// Declaration for cycle time measurement and time measurement
#define RESETTIME 0  // reset memory of Time Measurement; µs
#define READMIN 1    // read Time Measurement Minimum; µs
#define READCUR 2    // read Time Measurement Current; µs
#define READMAX 3    // read Time Measurement Maximim; µs

extern unsigned long cycleTime;                      // Unit ; µs : 0µs
extern unsigned long MeasTime;

bool timerFunction(int type, int timerNumber, bool inputSignal, unsigned long delayTime);
unsigned long cycleTimeMeasurement(int mode);
unsigned long timeMeasurement(int mode);