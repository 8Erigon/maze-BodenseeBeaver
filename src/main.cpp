#include <Arduino.h>
#include "../lib/General/General.h"
#include "../lib/MatrixVector/vektors.h"
#include "../lib/Timer/timer.h"


float RoboHeading = 0;
float RoboHeadingNew = 0;
float RoboHeadingFinal = 0;


bool isfirstRun = true;

// Defines

// Geschwindichkeiten
#define ROBOT_DRIVE_SPEED 72
#define MAX_ROBOT_ROTATION_SPEED 200
#define MIN_ROBOT_ROTATION_SPEED 37
#define ROBOT_RAMP_SPEED_UPWARDS 81
#define ROBOT_RAMP_SPEED_DOWNWARDS 33
#define RAMP_DOWNWARDS_FLIP_PREVENTION_SPEED 200

// Rampe
#define ACKNOLEGE_RAMP_UP_DEGREES 13
#define ACKNOLEGE_RAMP_DOWN_DEGREES -5

// Allgemeine Platendinge
#define PLATE_LENGHT 320
#define ACKNOLEGE_WALL_DISTANCE 180

// Perfekte Distanzen
#define PERFECT_FRONT_DISTANCE 60
#define PERFECT_BACK_DISTANCE 68
#define PERFECT_RIGHT_DISTANCE 86
#define PERFECT_LEFT_DISTANCE 83

// Seiten Korrektur
#define TIME_TO_DRIVE_SIDE_CORRECTION 150000
#define MAX_TIME_TO_ROTATE_DURING_SIDE_CORRECTION 4000000
#define TOO_LITTLE_DISTANCE_FOR_SIDE_CORRECTION 80
#define EXTRA_POWER_FOR_LEFT_PID 50
#define EXTRA_POWER_FOR_RIGHT_PID 50

// Vorder und Hinter Korrektur
#define MAX_TIME_TO_DRIVE_DURING_FRONT_CORRECTION 2000000
#define MAX_TIME_TO_DRIVE_DURING_BACK_CORRECTION 2000000

// Obstacle
#define MAX_TIME_TO_ROTATE_DURING_OBSTACLE_HIT 4000000

// Errors
#define MAX_FRONT_DISTANCE_ERROR 2
#define MAX_BACK_DISTANCE_ERROR 2
#define MAX_RIGHT_DISTANCE_ERROR 30
#define MAX_LEFT_DISTANCE_ERROR 30

//Servo
#define MIDDLE_SERVO_POS 90
#define MIDDLE_FROM_RIGHT_SERVO_POS 80
#define MIDDLE_FROM_LEFT_SERVO_POS 100
#define RIGHT_SERVO_POS 165
#define LEFT_SERVO_POS 15

//Lanbao Tof
#define DEFAULT_AMOUNT_OF_TILES_TO_ADD 3
#define MAX_WALL_ACKNOWLEDGE_DISTANCE 1000

//MazeMap
#define PLATE_SIZE_MM 300
#define MS_FOR_DRIVING_1m_RAMP_UP 1700 // Dummy Value
#define MS_FOR_DRIVING_1m_RAMP_DOWN 1700 // Dummy Value
#define ROUND_MAX_VALUE_FOR_HEIGHT 150 // +- Dieses Werts

extern bool robotCompletedRightWallDrivePath;

//enums
enum plateTypes : uint8_t
{
    WHITE_PLATE,
    BLACK_HOLE,
    CHECKPOINT,
    BLUE_PUDDLE
};

enum victimTypes : uint8_t
{
    NOTHING,
    U_VICTIM,
    S_VICTIM,
    H_VICTIM,
    GREEN_VICTIM,
    YELLOW_VICTIM,
    RED_VICTIM
};

// Switches
extern bool startSwitchIsOn;

extern bool SingleStepModeSwitchIsOn;
extern bool debugWindowSwitchIsOn;
extern bool SW11;
extern bool SW12;

// Buttons
extern bool resetCycleTimeButtonIsPressed;
extern bool resetChainButtonIsPressed;
extern bool singleStepButtonIsPressed;
extern bool cycleDebugWindowButtonIsPressed;
extern bool BTN5;
extern bool mazeMapPrintButtonIsPressed;

// VL Tofs
extern uint8_t distanceFrontRightSide;
extern uint8_t distanceFrontLeftSide;
extern uint8_t averageDistanceFront;

extern uint8_t distanceRightFrontSide;
extern uint8_t distanceRightBackSide;
extern uint8_t averageDistanceRight;

extern uint8_t distanceBackRightSide;
extern uint8_t distanceBackLeftSide;
extern uint8_t averageDistanceBack;

extern uint8_t distanceLeftFrontSide;
extern uint8_t distanceLeftBackSide;
extern uint8_t averageDistanceLeft;

extern bool disableVlTofs;

//Lanbao Tofs
extern uint16_t distanceFrontMiddle;
extern uint16_t distanceRightMiddle;
extern uint16_t distanceBackMiddle;
extern uint16_t distanceLeftMiddle;
extern bool disableLanbaoTofs;

// Colorsenor
extern uint16_t red;
extern uint16_t blue;
extern uint16_t green;
extern uint16_t clear;
extern bool disableColorSensor;

// Walls
extern bool hasWallFront;
extern bool hasWallBack;
extern bool hasWallRight;
extern bool hasWallLeft;

// Ramps, stairs and bumper
extern bool hasStairUp;
extern bool hasBumper;
extern unsigned long rampTime;
extern unsigned long stairTime;

//Display
extern bool disableDisplay;

// Bno
extern float robotHeading;
extern float robotPitch;
extern float robotRoll;
extern float robotAccX;
extern float robotAccY;
extern float robotAccZ;

extern float bnoOffsetCalbHeading;
extern float bnoOffsetCalbPitch;
extern float bnoOffsetCalbRoll;

extern float bnoCalbHeading;
extern float bnoCalbPitch;
extern float bnoCalbRoll;
extern float angleTarget;
extern float bnoCalbAccX;
extern float bnoCalbAccY;
extern float bnoCalbAccZ;

extern float last100PitchValues[100];
extern int currentLastPitchValue;


// Color Sensor
extern bool isOnBlackTile;
extern bool isOnBlueTile;
extern bool isOnControllTile;
extern plateTypes currentTileType;

// Leds
extern bool victimLedMode;
extern bool startLedMode;

extern bool LifeClockLEDIsOn;

// Victims
extern bool victimHarm;
extern bool victimStable;
extern bool victimRed;
extern bool victimYellow;
extern bool hasVictim;
extern char leftCameraResponse;
extern char rightCameraResponse;
extern victimTypes victimForMap;

// Servo
extern int servoPos;

// StepChain
extern int step;
extern int lastStep;
extern int nextStep;
extern int stepToJumpBackTo;
extern bool isFirstRun;
extern bool stepHasChanged;
extern bool processIsRunning;
extern bool singleStepFlag;
extern bool singleStep;
extern bool chainFlag; //?
extern bool chainFlagAngleTarget;
extern bool ignoreNextPlateAddition;

// Debug
extern bool debugWindowFlag;

// Correction
extern float degreeOffset;
extern float angleToFixSideWallDistance; 

// PID
// Rotation PID
// Final
extern double proportionalConstantForRotation;
extern double integralConstantForRotation;
extern double differentialConstantForRotation;

extern int maxIntegralValueForRotation;
extern int maxOutputSpeedForRotation;
extern int minOutputSpeedForRotation;

extern double degreeAccuracyForRotation;
extern double speedAccuracyForRotation;
extern double integralNewPointForRotation;

// Programm Input
extern bool doPIDForRotation;
extern float degreesToRotateForRotation;

// Processing
extern double bnoSetpointForRotation;
extern double bnoOffsetForRotation;
extern double errorForRotation;

extern double previousIntegralForRotation;
extern double previouserrorForRotation;
extern double previousmessungForRotation;

extern double differenceMeasurementForRotation;
extern double currentRotationForRotation;

// Output
extern double outputSpeedForRotation;


// Drive PID
extern bool doDrivePID;

extern double bnoSetpointForDrive;
extern double bnoOffsetForDrive;

extern double errorForDrive;
extern double previousErrorForDrive;
extern double integralForDrive;
extern double previousIntegralForDrive;
extern double proportionalForDrive;

extern double maxIntegralValueForDrive;
extern double maxOutputValueDifferenceForDrive;

extern double integralNewPointForDrive;

extern double integralConstantForDrive;
extern double proportionalConstantForDrive;
// End PID

// Multiplexer
extern QWIICMUX muxFront;
extern QWIICMUX muxBack;

//MazeMap
bool robotCompletedRightWallDrivePath = false;

// Switches
bool startSwitchIsOn = false;

bool SingleStepModeSwitchIsOn = false;
bool debugWindowSwitchIsOn = false;
bool SW11 = false;
bool SW12 = false;

// Buttons
bool resetCycleTimeButtonIsPressed = false;
bool resetChainButtonIsPressed = false;
bool singleStepButtonIsPressed = false;
bool cycleDebugWindowButtonIsPressed = false;
bool BTN5 = false;
bool mazeMapPrintButtonIsPressed = false;

// VL Tofs
uint8_t distanceFrontRightSide = 0;
uint8_t distanceFrontLeftSide = 0;
uint8_t averageDistanceFront = 0;

uint8_t distanceRightFrontSide = 0;
uint8_t distanceRightBackSide = 0;
uint8_t averageDistanceRight = 0;

uint8_t distanceBackRightSide = 0;
uint8_t distanceBackLeftSide = 0;
uint8_t averageDistanceBack = 0;

uint8_t distanceLeftFrontSide = 0;
uint8_t distanceLeftBackSide = 0;
uint8_t averageDistanceLeft = 0;

bool disableVlTofs = false;

//Lanbao Tofs
uint16_t distanceFrontMiddle = false;
uint16_t distanceRightMiddle = false;
uint16_t distanceBackMiddle = false;
uint16_t distanceLeftMiddle = false;
bool disableLanbaoTofs = false;

// Colorsenor
uint16_t red = 0;
uint16_t blue = 0;
uint16_t green = 0;
uint16_t clear = 0;
bool disableColorSensor = false;

// Walls
bool hasWallFront = false;
bool hasWallBack = false;
bool hasWallRight = false;
bool hasWallLeft = false;

// Ramps, stairs and bumper
bool hasStairUp = false;
bool hasBumper = false;
unsigned long rampTime = 0;                       // Unit ; µs : 0µs
unsigned long stairTime = 0;                       // Unit ; µs : 0µs

// Bno
float robotHeading = 0;
float robotPitch = 0;
float bnoOffsetCalbHeading = 0;
float bnoOffsetCalbPitch = 0;
float bnoCalbHeading = 0;
float bnoCalbPitch = 0;
float angleTarget = 0;
float robotAccX = 0;
float robotAccY = 0;
float robotAccZ = 0;

float last100PitchValues[100] = {};
int currentLastPitchValue = 0;

// Color Sensor
bool isOnBlackTile = false;
bool isOnBlueTile = false;
bool isOnControllTile = false;
plateTypes currentTileType = CHECKPOINT;

//Display
bool disableDisplay = false;

// Leds
bool victimLedMode = false;
bool startLedMode = false;

bool LifeClockLEDIsOn = false;

// Victims
bool victimHarm = false;
bool victimStable = false;
bool victimRed = false;
bool victimYellow = false;
bool hasVictim = false;
char leftCameraResponse = 'X';
char rightCameraResponse = 'X';
victimTypes victimForMap;

// Servo
int servoPos = 90;

// StepChain
int step = 0;
int lastStep = 0;
int nextStep = 0;
int stepToJumpBackTo = -1;
bool isFirstRun = true;
bool stepHasChanged = false;
bool processIsRunning = false;
bool singleStepFlag = false;
bool singleStep = false;
bool chainFlag = false;
bool chainFlagAngleTarget = false;
bool ignoreNextPlateAddition = false;

//Debug
bool debugWindowFlag = false;

// Correction
float degreeOffset = 0;
float angleToFixSideWallDistance = 0; 
// PID
// Rotation PID
// Final
double proportionalConstantForRotation = 2.0;
double integralConstantForRotation = 22.0;
double differentialConstantForRotation = 20.0;

int maxIntegralValueForRotation = 170;
int maxOutputSpeedForRotation = MAX_ROBOT_ROTATION_SPEED;
int minOutputSpeedForRotation = 32;

double degreeAccuracyForRotation = 0.6;
double speedAccuracyForRotation = 40.0;
double integralNewPointForRotation = 30.0;

// Programm Input
bool doPIDForRotation = false;
float degreesToRotateForRotation = 0;

// Processing
double bnoSetpointForRotation = 0;
double bnoOffsetForRotation = 0;
double errorForRotation = 0;

double previousIntegralForRotation = 0;
double previouserrorForRotation = 0;
double previousmessungForRotation = 0;

double differenceMeasurementForRotation = 0;
double currentRotationForRotation = 0;

// Output
double outputSpeedForRotation = 0;


// Drive PID
bool doDrivePID = false;

double bnoSetpointForDrive = 0;
double bnoOffsetForDrive = 0;

double errorForDrive = 0;
double previousErrorForDrive = 0;
double integralForDrive = 0;
double previousIntegralForDrive = 0;
double proportionalForDrive = 0;

double maxIntegralValueForDrive = 60;
double maxOutputValueDifferenceForDrive = 70;

double integralNewPointForDrive = 3;

double integralConstantForDrive = 60;
double proportionalConstantForDrive = 120;
// End PID
void calculateVictim(char victimAsChar) {
    
    switch (victimAsChar)
    {
    case 'H':
        victimHarm = true;
        victimForMap = H_VICTIM;
        break;
    case 'S':
        victimStable = true;
        victimForMap = S_VICTIM;
        break;
    case 'U':
        victimForMap = U_VICTIM;
        break;
    case 'R':
        victimRed = true;
        victimForMap = RED_VICTIM;
        break;
    case 'Y':
        victimYellow = true;
        victimForMap = YELLOW_VICTIM;
        break;
    case 'G':
        victimForMap = GREEN_VICTIM;
        break;
    case 'D':
    // Später deactivated in die Map eintragen für information von wann bis wann eine Kamera nicht ansprechbar war
        victimForMap = NOTHING;
        break;
    default:
        victimForMap = NOTHING;
        break;
    }
    hasVictim = victimForMap != NOTHING;
    
}
float calcDegreesToRotate(){
    float result = angleTarget-bnoCalbHeading;
    if(result > 180){
        result = result - 360;
    }else if(result < -180){
        result = result + 360;
    }
    if(stepHasChanged){
        Serial.println("calc Result: " + (String)result);
        Serial.println("calc Tar: "+(String)angleTarget);
        Serial.println("calc Head: "+(String)bnoCalbHeading);
    }
    return result;
}

/*
---------------------------------------------------------
----------------------Main-------------------------------
---------------------------------------------------------
*/


int main()
{
  // Power On
  // Initialize
  Serial.begin(9600);
  Serial.println("---Begin programm---");
  Robot robo = Robot();

  while (true)
  {
    // Funktionen vor der Schrittkette ********************************************
    //processImageInputs();

    // LifeClock
    //LifeClockLEDIsOn = !LifeClockLEDIsOn;

    // Steuerung Schrittkette *****************************************************
    // Reset Process
    if (robo.readButton(BUTTON1))// resetchain button
    {
      step = 0;
      lastStep = 0;
      processIsRunning = false;
    }

    // Restart Process
    if (!robo.readSwitch(StartSwitch) && processIsRunning)
    {
      step = 1000;
      lastStep = 1000;
      processIsRunning = false;
    }

    // Single Step
    if (!(robo.readButton(BUTTON2) && robo.readSwitch(SWITCH10))) // Single stepp button & singlestep switch
      singleStepFlag = false;
    singleStep = (timerFunction(TON, TBUTTONSINGLESTEP, (robo.readButton(BUTTON2) && robo.readSwitch(SWITCH10)), 100000) && !singleStepFlag); // Entprellzeit 100ms
    if (singleStep)
      singleStepFlag = true;

    // In single step mode restore last step
    if (robo.readButton(BUTTON1) || (!singleStep && robo.readSwitch(SWITCH10)))
      step = lastStep;

    // Step Change
    if (step != lastStep)
    {
      stepHasChanged = true;
    }
    else
    {
      stepHasChanged = false;
    }

    // Step Display
    lastStep = step;

    // Schrittkette ****************************************************************
    switch (step)
    {
    case 0:
      // Anfang Kette, Start Schritt, ohne Aktionen
      step = 10;
      break;

    case 10:
      // Initialisierung, Reset Timer
      //startLedMode = false;
      //disableVlTofs = false;
      processIsRunning = false;
      
      //bnoOffsetCalbHeading = robotHeading;
     // bnoOffsetCalbPitch = robotPitch;
     // angleTarget = 0;
      step = 20;
      break;

    case 20:
      robo.move.Stop(0);
      step = 30;
      break;

    case 30:
      // Servo in Grundstellung
      servoPos = MIDDLE_SERVO_POS;
      step = 40;
      break;
    
    /*case 31:
      //Servo test remove later
      if (stepHasChanged) {
        servoPos = LEFT_SERVO_POS;
      }
      if (timerFunction(TON, TCHAIN1, !stepHasChanged, 2000000))
        step = 32;
      break;
    case 32:
        servoPos = MIDDLE_FROM_LEFT_SERVO_POS;
      if (timerFunction(TON, TCHAIN1, !stepHasChanged, 2000000))
        step = 31;
      break;*/

    case 40:
      // Reset Anzeigen
      robo.setLedColor(WRGB::NONE);
      robo.bottomExpander1.output(LED5, !OFF); // invertierung damit true = an und false = aus
      robo.bottomExpander1.output(LED6, !OFF); // invertierung damit true = an und false = aus
      robo.bottomExpander1.output(LED7, !OFF); // invertierung damit true = an und false = aus
      robo.bottomExpander1.output(LED8, !OFF); // invertierung damit true = an und false = aus
      step = 45; // Später zu 50 ändern
      break;
    case 45:
      // Delay damit die Kameras zum booten zeit haben
      if (timerFunction(TON, TCHAIN1, !stepHasChanged, 3000000))
        step = 50;
      break;
    case 50:
      // Kamera recht zurüclksetzen
      if (stepHasChanged)
        chainFlag = true;
      if (rightCamera.resetCamera(stepHasChanged)) {
        victimType = rightCamera.getVictim();
        chainFlag = false;
      }
      if (!chainFlag)
        step = 60;
      break;

    case 60:
      // Kamera links zurücksetzen
      if (stepHasChanged)
        chainFlag = true;
      if (leftCamera.resetCamera(stepHasChanged)) {
        victimType = leftCamera.getVictim();
        chainFlag = false;
      }
      if (!chainFlag)
        step = 70;
      break;

    case 70:
      // Reset Suchstrategie, Karte (Noch Nicht implementiert)
      step = 90;
      break;

    case 90:
      // Aussprung
      step = 100;
      break;

    case 100:
      // Warte auf Starttaster
      startLedMode = true;
      if (robo.readSwitch(StartSwitch)) {
        startLedMode = false;
        processIsRunning = true;
        step = 110;
      }
      break;

    case 110:
      // Beruhigungszeit
      if (timerFunction(TON, TCHAIN1, !stepHasChanged, 2000000))
        step = 120;
      break;

    case 120: // Kompass auf Null setzen
      bno.init();
      step = 130;
      break;

    case 130:

      bnoOffsetCalbHeading = robotHeading;
      bnoOffsetCalbPitch = robotPitch;
      angleTarget = 0;
      if (timerFunction(TON, TCHAIN1, !stepHasChanged, 1000000)) step = 190;
      break;

    case 190:
      // Aussprung
      step = 200;
      break;

    case 200:
      // Fahre Vorwärts Einsprung
      step = 210;
      break;

    case 210:
      // Fahre zum nächten Feld vorwärts, Time Measurement, Sensor Schwarzes Feld
      if(stepHasChanged)
      robo.move.speed = ROBOT_DRIVE_SPEED;
      robo.move.goalAngle = robo.orientation.heading;
      // Start Zeitmessung
      if (stepHasChanged) {
        chainFlag = true;
        MeasTime = timeMeasurement(RESETTIME);
      }
      // Start Kamera
      if (chainFlag && timerFunction(TON, TCHAIN2, !stepHasChanged, 400000)) {
        chainFlag = false;
        rightCamera.startScanning();
        leftCamera.startScanning();
      }
      // Stop Motor Zeit
      if (timerFunction(TON, TCHAIN1, !stepHasChanged, 1000000)) {
        robo.move.speed = 0;
        step = 212;
      }
      // Schwarzes Feld
      if (isOnBlackTile) {
        robo.move.speed = 0;
        MeasTime = timeMeasurement(READCUR);
        step = 2200;
      }
      if (bnoCalbPitch > 10){
        robo.move.speed = 0;
        MeasTime = timeMeasurement(READCUR);
        step = 2000;
      }
      if (bnoCalbPitch < -10) {
        robo.move.speed = 0;
        MeasTime = timeMeasurement(READCUR);
        step = 2100;
      }
      break;
  	
    case 212:
      if (timerFunction(TON, TCHAIN1, !stepHasChanged, 500000)) {
        step = 215;
      }
      break;
    
    case 215:
      // Nachpositionierung mit Front sensoren
      if (!hasWallFront || bnoCalbPitch>5 || bnoCalbPitch<-5) {
        step = 220;
        break;
      }
      if (movement.doFrontCorrection((distanceNorthLeft + distanceNorthRight) / 2))
        step = 220;
      break;

    case 220:
      // Sprungverteiler neues Feld
      step = 250; // standardTile
      if (isOnControllTile)
        step = 240;
      if (isOnBlueTile)
        step = 230;
      break;

    case 230:
      // Blaues Feld
      // Stop Kamera
      leftCamera.stopScanningAndRequestVictim(stepHasChanged);
      rightCamera.stopScanningAndRequestVictim(stepHasChanged);
      // 5 sec warten
      robo.move.speed = 0;
      if (timerFunction(TON, TCHAIN1, !stepHasChanged, 5000000)) {
        step = 800;
      }
      break;

    case 240:
      // Controll Feld
      // Stop Kamera
      leftCamera.stopScanningAndRequestVictim(stepHasChanged);
      rightCamera.stopScanningAndRequestVictim(stepHasChanged);
      step = 800;
      break;

    case 250:
      // Standard Feld
      step = 300;
      break;

    case 300:
      // Stop Kamera und warte bis diese die daten gesendet hat
      if (stepHasChanged)
        chainFlag = true;
      rightCamera.stopScanningAndRequestVictim(stepHasChanged);
      leftCamera.stopScanningAndRequestVictim(stepHasChanged);
      if (rightCamera.requestIsCompleted() && leftCamera.requestIsCompleted()) {
        chainFlag = false;
      }
      if (!chainFlag)
        step = 305;
      break;

    case 305:
      // Wand rechts vorhanden
      step = 400;
      if (hasWallRight)
        step = 310;
      break;

    case 310:
      // Rechte Kamera Auswertung
      if (stepHasChanged)
        victimType = rightCamera.getVictim();
      calculateVictim(victimType);
      step = 400;
      if (hasVictim)
        step = 320;
      break;

    case 320:
      // Blinker 5s
      victimLedMode = timerFunction(TFLASH, TCHAIN3, !stepHasChanged, 250000);
      if (timerFunction(TON, TCHAIN1, !stepHasChanged, 5000000)) {
        victimLedMode = OFF;
        step = 330;
      }
      break;

    case 330:
      // Abwurf Rescue Kits ?
      step = 400; // kein Rescue Kit
      if (victimHarm)
        step = 350;
      if (victimStable)
        step = 370;
      if (victimRed)
        step = 350;
      if (victimYellow)
        step = 370;
      break;

    case 350:
      // Abwurf Kit 2
      if (stepHasChanged) {
        servoPos = RIGHT_SERVO_POS;
      }
      if (timerFunction(TON, TCHAIN1, !stepHasChanged, 2000000))
        step = 360;
      break;

    case 360:
      // Servo Grundstellung
      if (stepHasChanged) {
        servoPos = MIDDLE_FROM_RIGHT_SERVO_POS;
      }
      if (timerFunction(TON, TCHAIN1, !stepHasChanged, 2000000))
        step = 370;
      break;

    case 370:
      // Abwurf Kit 1
      if (stepHasChanged) {
        servoPos = RIGHT_SERVO_POS;
      }
      if (timerFunction(TON, TCHAIN1, !stepHasChanged, 2000000))
        step = 380;
      break;

    case 380:
      // Servo Grundstellung
      if (stepHasChanged) {
        servoPos = MIDDLE_FROM_RIGHT_SERVO_POS;
      }
      if (timerFunction(TON, TCHAIN1, !stepHasChanged, 2000000))
        step = 400;
      break;

    case 400:
      // Wand links vorhanden
      step = 500;
      if (hasWallLeft)
        step = 410;
      break;

    case 410:
      // Kamer Links Auswertung
      if (stepHasChanged)
        victimType = leftCamera.getVictim();
      calculateVictim(victimType);
      step = 500;
      if (hasVictim)
        step = 420;
      break;

    case 420:
      // Blinker 5s
      victimLedMode = timerFunction(TFLASH, TCHAIN3, !stepHasChanged, 250000);
      if (timerFunction(TON, TCHAIN1, !stepHasChanged, 5000000)) {
        victimLedMode = OFF;
        step = 430;
      }
      break;

    case 430:
      // Abwurf Rescue Kits ?
      step = 500; // kein Rescue Kit
      if (victimHarm)
        step = 450;
      if (victimStable)
        step = 470;
      if (victimRed)
        step = 450;
      if (victimYellow)
        step = 470;
      break;

    case 450:
      // Abwurf Kit 2
      if (stepHasChanged) {
        servoPos = LEFT_SERVO_POS;
      }
      if (timerFunction(TON, TCHAIN1, !stepHasChanged, 2000000))
        step = 460;
      break;

    case 460:
      // Servo Grundstellung
      if (stepHasChanged) {
        servoPos = MIDDLE_FROM_LEFT_SERVO_POS;
      }
      if (timerFunction(TON, TCHAIN1, !stepHasChanged, 2000000))
        step = 470;
      break;

    case 470:
      // Abwurf Kit 1
      if (stepHasChanged) {
        servoPos = LEFT_SERVO_POS;
      }
      if (timerFunction(TON, TCHAIN1, !stepHasChanged, 2000000))
        step = 480;
      break;

    case 480:
      // Servo Grundstellung
      if (stepHasChanged) {
        servoPos = MIDDLE_FROM_LEFT_SERVO_POS;
      }
      if (timerFunction(TON, TCHAIN1, !stepHasChanged, 2000000))
        step = 500;
      break;

      // Wand vorne vorhanden *****
    case 500:
      // Wand vorne vorhanden
      step = 800;
      if (hasWallFront)
        step = 510;
      break;

    case 510:
      // Auswahl Drehung (Priorität rechts)
      step = 600;
      if (hasWallLeft)
        step = 600;
      if (hasWallRight)
        step = 700;
      break;

    case 600:
      // Drehen 90° rechts
      if (stepHasChanged) {
        chainFlag = true;
        angleTarget = updateAngleTarget(90);
      }

      // Start Kamera links
      if (chainFlag && timerFunction(TON, TCHAIN2, !stepHasChanged, 250000)) {
        chainFlag = false;
        leftCamera.startScanning();
      }
      if (movement.rotateDegreesWithPID(calcDegreesToRotate(), stepHasChanged))
        step = 605; // Position erreicht
      break;

    case 605:
      // Kameras Links auslesen
      if (leftCamera.stopScanningAndRequestVictim(stepHasChanged))
        step = 610;
      break;

    case 610:
      // Kamera Auswertung Links
      if (stepHasChanged)
        victimType = leftCamera.getVictim();
      calculateVictim(victimType);
      step = 880;
      if (hasVictim)
        step = 620;
      break;

    case 620:
      // Blinker 5s
      victimLedMode = timerFunction(TFLASH, TCHAIN3, !stepHasChanged, 250000);
      if (timerFunction(TON, TCHAIN1, !stepHasChanged, 5000000)) {
        victimLedMode = OFF;
        step = 630;
      }
      break;

    case 630:
      // Abwurf Rescue Kits ?
      step = 880; // kein Rescue Kit
      if (victimHarm)
        step = 650;
      if (victimStable)
        step = 670;
      if (victimRed)
        step = 650;
      if (victimYellow)
        step = 670;
      break;

    case 650:
      // Abwurf Kit 2
      if (stepHasChanged) {
        servoPos = LEFT_SERVO_POS;
      }
      if (timerFunction(TON, TCHAIN1, !stepHasChanged, 2000000))
        step = 660;
      break;

    case 660:
      // Servo Grundstellung
      if (stepHasChanged) {
        servoPos = MIDDLE_FROM_LEFT_SERVO_POS;
      }
      if (timerFunction(TON, TCHAIN1, !stepHasChanged, 2000000))
        step = 670;
      break;

    case 670:
      // Abwurf Kit 1
      if (stepHasChanged) {
        servoPos = LEFT_SERVO_POS;
      }
      if (timerFunction(TON, TCHAIN1, !stepHasChanged, 2000000))
        step = 680;
      break;

    case 680:
      // Servo Grundstellung
      if (stepHasChanged) {
        servoPos = MIDDLE_FROM_LEFT_SERVO_POS;
      }
      if (timerFunction(TON, TCHAIN1, !stepHasChanged, 2000000))
        step = 880;
      break;

    case 700:
      // Drehen 90° links
      if (stepHasChanged) {
        angleTarget = updateAngleTarget(-90);
        chainFlag = true;
      }
      // Start Kamera rechts
      if (chainFlag && timerFunction(TON, TCHAIN2, !stepHasChanged, 250000)) {
        chainFlag = false;
        rightCamera.startScanning();
      }
      if (movement.rotateDegreesWithPID(calcDegreesToRotate(), stepHasChanged))
        step = 705; // Position erreicht
      break;

    case 705:
      // Kameras Rechts auslesen
      if (rightCamera.stopScanningAndRequestVictim(stepHasChanged))
        step = 710;
      break;

    case 710:
      // Kamera Auswertung Rechts
      if (stepHasChanged)
        victimType = rightCamera.getVictim();
      calculateVictim(victimType);
      step = 800;
      if (hasVictim)
        step = 720;
      break;

    case 720:
      // Blinker 5s
      victimLedMode = timerFunction(TFLASH, TCHAIN3, !stepHasChanged, 250000);
      if (timerFunction(TON, TCHAIN1, !stepHasChanged, 5000000)) {
        victimLedMode = OFF;
        step = 730;
      }
      break;

    case 730:
      // Abwurf Rescue Kits ?
      step = 800; // kein Rescue Kit
      if (victimHarm)
        step = 750;
      if (victimStable)
        step = 770;
      if (victimRed)
        step = 750;
      if (victimYellow)
        step = 770;
      break;

    case 750:
      // Abwurf Kit 2
      if (stepHasChanged) {
        servoPos = RIGHT_SERVO_POS;
      }
      if (timerFunction(TON, TCHAIN1, !stepHasChanged, 2000000))
        step = 760;
      break;

    case 760:
      // Servo Grundstellung
      if (stepHasChanged) {
        servoPos = MIDDLE_FROM_RIGHT_SERVO_POS;
      }
      if (timerFunction(TON, TCHAIN1, !stepHasChanged, 2000000))
        step = 770;
      break;

    case 770:
      // Abwurf Kit 1
      if (stepHasChanged) {
        servoPos = RIGHT_SERVO_POS;
      }
      if (timerFunction(TON, TCHAIN1, !stepHasChanged, 2000000))
        step = 780;
      break;

    case 780:
      // Servo Grundstellung
      if (stepHasChanged) {
        servoPos = MIDDLE_FROM_RIGHT_SERVO_POS;
      }
      if (timerFunction(TON, TCHAIN1, !stepHasChanged, 2000000))
        step = 800;
      break;

      // Berechnung Weiterfahrt *****
    case 800:
      // Berechnung Weiterfahrt
      step = 860;
      if (!hasWallLeft)
        step = 850;
      if (!hasWallFront)
        step = 880;
      if (!hasWallRight)
        step = 860;
      if (hasWallLeft && hasWallFront && hasWallRight)
        step = 870;
      break;

    case 850:
      // Drehen 90° links
      if(stepHasChanged) {
        angleTarget = updateAngleTarget(-90);
        chainFlag = true;
      }
      if (movement.rotateDegreesWithPID(calcDegreesToRotate(), stepHasChanged))
        step = 890; // Position erreicht
      break;

    case 860:
      // Drehen 90° rechts
      if(stepHasChanged) angleTarget = updateAngleTarget(90);
      if (movement.rotateDegreesWithPID(calcDegreesToRotate(), stepHasChanged))
        step = 890;
      break;

    case 870:
      // Drehen 180°
      if(stepHasChanged) angleTarget = updateAngleTarget(180);
      if (movement.rotateDegreesWithPID(calcDegreesToRotate(), stepHasChanged))
        step = 890; // Position erreicht
      break;

    case 880:
      // keine Drehen
      step = 890;
      break;

    case 890:
      // Weiter mit Nachpositionierung
      step = 900;
      break;

      // Nachpositionierung *****
    case 900:
      // Nachpositionierung mit Front sensoren
      if (!hasWallFront) {
        step = 910;
        break;
      }
      if (movement.doFrontCorrection((distanceNorthLeft + distanceNorthRight) / 2))
        step = 920;
      break;

    case 910:
      // Nachpositionierung mit Rücken sensoren
      if (!hasWallBack) {
        step = 920;
        break;
      }
      if (movement.doBackCorrection(distanceSouthLeft)) {
        step = 920;
      }

      break;

    case 920:
      step = 930;
      break;

    case 930:
      step = 940;
      break;

    case 940:
      //Nachpositienierung zur Mitte der platte mithilfe der Rechten sensoren
      step = 950;
      break;

    case 950:
      //Nachpositienierung zur Mitte der platte mithilfe der Linken sensoren
      step = 960;
      break;

    case 960:
      //
      step = 970;
      break;

    case 970:
      //Winkelausrichtung
      if (movement.rotateDegreesWithPID(calcDegreesToRotate(), stepHasChanged))
        step = 980;
      break;

    case 980:
      //
      step = 990;
      break;

    case 990:
      // Start Weiterfahrt
      step = 200; // Test 110
      break;

      // Schrittkette ausgelagerte Funktionen *******************************
      // Restart
    case 1000:
      // Anfang Kette Restart, Start Schritt, ohne Aktionen
      step = 1010;
      break;

    case 1010:
      // // Initialisierung, Reset Timer
      step = 1020;
      break;

    case 1020:
      robo.move.speed = 0;
      step = 1030;
      break;

    case 1030:
      servoPos = MIDDLE_SERVO_POS;
      step = 1040;
      break;

    case 1040:
      // Reset Anzeigen
      startLedMode = OFF;
      victimLedMode = OFF;
      step = 1050;
      break;

    case 1050:
      //
      step = 1060;
      break;

    case 1060:
      // Suchstrategie, Karte, Setze Karte auf letzten Kontrollpunkt
      step = 1090;
      break;

    case 1090:
      //
      step = 1100;
      break;


    case 1100:
      // Warte auf Starttaster
      startLedMode = timerFunction(TFLASH, TCHAIN1, !stepHasChanged, 250000);
      if (robo.readSwitch(StartSwitch)) {
        startLedMode = OFF;
        processIsRunning = true;
        step = 1110;
      }
      break;

    case 1110:
      //Angle target richtig setzen für aktuelle rotierung
      if(bnoCalbHeading>=315||bnoCalbHeading<=45)
        angleTarget = 0;
      else if(bnoCalbHeading<=135)
        angleTarget = 90;
      else if(bnoCalbHeading<=225)
        angleTarget = 180;
      else
        angleTarget = 270;
      step = 1120;
      break;

    case 1120:
      //Tof an mache
      disableVlTofs = false;
      step = 1130;
      break;

    case 1130:
      // Start Weiterfahrt vorwärts
      step = 200; // Test 110
      break;

      // Rampe Aufwärts *****
    case 2000:
      // Einsprung Rampe Aufwärts
      step = 2010;
      break;

    case 2010:
      // Stoppe Kameras vor Rampe
      leftCamera.stopScanningAndRequestVictim(stepHasChanged);
      rightCamera.stopScanningAndRequestVictim(stepHasChanged);
      step = 2020;
      break;

    case 2020:
      // Start Motor Rampe aufwärts
      robo.move.speed = ROBOT_RAMP_SPEED_UPWARDS;
      robo.move.goalAngle = robo.orientation.heading;
      if (bnoCalbPitch < 5 || distanceNorthLeft < 10) {
        robo.move.speed = 0;
        step = 2030;
      }
      break;

    case 2030:
      // Motor Nachlauf
      // Start Motor
      robo.move.speed = ROBOT_RAMP_SPEED_UPWARDS;
      robo.move.goalAngle = robo.orientation.heading;
      // Stop Motor Zeit
      if (timerFunction(TON, TCHAIN1, !stepHasChanged, 250000)) {
        robo.move.speed = 0;
        step = 2035;
      }
      break;

    case 2035:
      if (timerFunction(TON, TCHAIN1, !stepHasChanged, 500000)) {
        step = 2040;
      }
      break;

    case 2040:
      // Nachpositionierung Front
      if (!hasWallFront || bnoCalbPitch>5 || bnoCalbPitch<-5) {
        step = 2050;
        break;
      }
      if (movement.doFrontCorrection((distanceNorthLeft + distanceNorthRight) / 2))
        step = 2050;
      break;

    case 2050:
      // Setze Attribute (Rampe oben)
      step = 2090;
      break;

    case 2090:
      // Weiterfahrt + Feinpositionierung
      step = 500;
      break;

      // Rampe Abwärts *****
    case 2100:
      // Einsprung Rampe Abwärts
      step = 2110;
      break;

    case 2110:
      // Stoppe Kameras vor Rampe
      leftCamera.stopScanningAndRequestVictim(stepHasChanged);
      rightCamera.stopScanningAndRequestVictim(stepHasChanged);
      step = 2120;
      break;

    case 2120:
      // Start Motor Rampe abwärts
      robo.move.speed = ROBOT_RAMP_SPEED_DOWNWARDS;
      robo.move.goalAngle = robo.orientation.heading;
      if (bnoCalbPitch > -5 || distanceNorthLeft < 10) {
        robo.move.speed = 0;
        step = 2130;
      }
      break;

    case 2130:
      // Motor Nachlauf
      // Start Motor
      robo.move.speed = ROBOT_RAMP_SPEED_DOWNWARDS;
      robo.move.goalAngle = robo.orientation.heading;
      // Stop Motor Zeit
      if (timerFunction(TON, TCHAIN1, !stepHasChanged, 200000)) {
        robo.move.speed = 0;
        step = 2135;
      }
      break;

    case 2135:
      if (timerFunction(TON, TCHAIN1, !stepHasChanged, 500000)) {
        step = 2140;
      }
      break;

    case 2140:
      // Nachpositionierung Front
      if (!hasWallFront || bnoCalbPitch>5 || bnoCalbPitch<-5) {
        step = 2150;
        break;
      }
      if (movement.doFrontCorrection((distanceNorthLeft + distanceNorthRight) / 2))
        step = 2150;
      break;

    case 2150:
      // Setze Attribute (Rampe unten)
      step = 2190;
      break;

    case 2190:
      // Weiterfahrt + Feinpositionierung
      step = 500;
      break;

      // Schwarze Platte *****
    case 2200:
      // Einsprung Schwarze Platte
      step = 2210;
      break;

    case 2210:
      // Stoppe Kameras vor schwarzer Platte
      leftCamera.stopScanningAndRequestVictim(stepHasChanged);
      rightCamera.stopScanningAndRequestVictim(stepHasChanged);
      step = 2220;
      break;

    case 2220:
      // Start Motor rückwärts
      movement.driveAtSpeed(backward, ROBOT_DRIVE_SPEED);
      // Stop Motor Zeit
      if (timerFunction(TON, TCHAIN1, !stepHasChanged, MeasTime)) {
        robo.move.speed = 0;
        step = 2230;
      }
      break;

    case 2230:
      // Nachpositionierung mit Rücken sensoren
      if (!hasWallBack) {
        step = 2240;
        break;
      }
      if (movement.doBackCorrection(distanceSouthLeft)) {
        step = 2240;
      }
      break;

    case 2240:
      // Berechnung Weiterfahrt (Priorität rechts, Fahrzeug steht rückwärts)
      step = 800;
      if (!hasWallRight)
        step = 2260;
      if (!hasWallBack)
        step = 2270;
      if (!hasWallLeft)
        step = 2250;
      break;

    case 2250:
      // Drehen 90° links
      if(stepHasChanged)
        angleTarget = updateAngleTarget(-90);
      if (movement.rotateDegreesWithPID(calcDegreesToRotate(), stepHasChanged))
        step = 2290; // Position erreicht
      break;

    case 2260:
      // Drehen 90° rechts
      if(stepHasChanged)
        angleTarget = updateAngleTarget(90);
      if (movement.rotateDegreesWithPID(calcDegreesToRotate(), stepHasChanged))
        step = 2290; // Position erreicht
      break;

    case 2270:
      // Drehen 180°
      if(stepHasChanged)
        angleTarget = updateAngleTarget(180);
      if (movement.rotateDegreesWithPID(calcDegreesToRotate(), stepHasChanged))
        step = 2290; // Position erreicht
      break;

    case 2280:
      // keine Drehen
      step = 2290;
      break;

    case 2290:
      // Weiter mit Nachpositionierung
      step = 900;
      break;

    default:
      step = 9999;
      break;
    }

    // Funktionen nach der Schrittkette *******************************************
    // Display Next Step
    nextStep = step;

    // Cycle Time Measurement
    if (resetCycleTimeButtonIsPressed || resetChainButtonIsPressed || isFirstRun)
    {
      cycleTime = cycleTimeMeasurement(RESETTIME);
    }
    else
    {
      cycleTime = cycleTimeMeasurement(READMAX);
    }

    // Display
    utils.writeTextToDisplay(0,
                             "CT: " + utils.getStringWithLenght(String(cycleTime / 1000), 5) + " " +
                                 "V: " + victimType + " " +
                                 "T: " + currentTileType);
    utils.writeTextToDisplay(1,
                             "LST: " + utils.getStringWithLenght(String(lastStep), 5) + " " +
                                 "NST: " + utils.getStringWithLenght(String(nextStep), 5));
    //utils.writeTextToDisplay(2, utils.getStringWithLenght(String(hasWallFront?1:0), 1)+utils.getStringWithLenght(String(hasWallRight?1:0), 1)+utils.getStringWithLenght(String(hasWallBack?1:0), 1)+utils.getStringWithLenght(String(hasWallLeft?1:0), 1));
    utils.writeTextToDisplay(2, "P: "+utils.getStringWithLenght((String)bnoCalbPitch, 4));

    processImageOutputs();
    //Serial.println("Ist: " + (String) bnoCalbHeading);
    //Serial.println("Soll: " + (String) angleTarget);
    isFirstRun = false;
  }
}


// put function definitions here:
