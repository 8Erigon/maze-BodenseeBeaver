#ifndef DOG_LIB
#define DOG_LIB
#include <Arduino.h>

// float RoboHeading = 0; //Redefinition
extern float RoboHeadingNew;
extern float RoboHeadingFinal;
extern bool isfirstRun;

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

extern bool robotCompletedRightWallDrivePath ;
extern bool startSwitchIsOn ;
extern bool SingleStepModeSwitchIsOn ;
extern bool debugWindowSwitchIsOn ;
extern bool SW11 ;
extern bool SW12 ;
extern bool resetCycleTimeButtonIsPressed ;
extern bool resetChainButtonIsPressed ;
extern bool singleStepButtonIsPressed ;
extern bool cycleDebugWindowButtonIsPressed ;
extern bool BTN5 ;
extern bool mazeMapPrintButtonIsPressed ;
extern uint8_t distanceFrontRightSide ;
extern uint8_t distanceFrontLeftSide ;
extern uint8_t averageDistanceFront ;
extern uint8_t distanceRightFrontSide ;
extern uint8_t distanceRightBackSide ;
extern uint8_t averageDistanceRight ;
extern uint8_t distanceBackRightSide ;
extern uint8_t distanceBackLeftSide ;
extern uint8_t averageDistanceBack ;
extern uint8_t distanceLeftFrontSide ;
extern uint8_t distanceLeftBackSide ;
extern uint8_t averageDistanceLeft ;
extern bool disableVlTofs ;
extern uint16_t distanceFrontMiddle ;
extern uint16_t distanceRightMiddle ;
extern uint16_t distanceBackMiddle ;
extern uint16_t distanceLeftMiddle ;
extern bool disableLanbaoTofs ;
extern uint16_t red ;
extern uint16_t blue ;
extern uint16_t green ;
extern uint16_t clear ;
extern bool disableColorSensor ;
extern bool hasWallFront ;
extern bool hasWallBack ;
extern bool hasWallRight ;
extern bool hasWallLeft ;
extern bool hasStairUp ;
extern bool hasBumper ;
extern unsigned long rampTime ;
extern unsigned long stairTime ;
extern float robotHeading ;
extern float robotPitch ;
extern float bnoOffsetCalbHeading ;
extern float bnoOffsetCalbPitch ;
extern float bnoCalbHeading ;
extern float bnoCalbPitch ;
extern float angleTarget ;
extern float robotAccX ;
extern float robotAccY ;
extern float robotAccZ ;
extern float last100PitchValues[100] ;
extern int currentLastPitchValue ;
extern bool isOnBlackTile ;
extern bool isOnBlueTile ;
extern bool isOnControllTile ;
extern plateTypes currentTileType ;
extern bool disableDisplay ;
extern bool victimLedMode ;
extern bool startLedMode ;
extern bool LifeClockLEDIsOn ;
extern bool victimHarm ;
extern bool victimStable ;
extern bool victimRed ;
extern bool victimYellow ;
extern bool hasVictim ;
extern char leftCameraResponse ;
extern char rightCameraResponse ;
extern victimTypes victimForMap;
extern int servoPos ;
extern int step ;
extern int lastStep ;
extern int nextStep ;
extern int stepToJumpBackTo ;
extern bool isFirstRun ;
extern bool stepHasChanged ;
extern bool processIsRunning ;
extern bool singleStepFlag ;
extern bool singleStep ;
extern bool chainFlag ;
extern bool chainFlagAngleTarget ;
extern bool ignoreNextPlateAddition ;
extern bool debugWindowFlag ;
extern float degreeOffset ;
extern float angleToFixSideWallDistance ;
extern double proportionalConstantForRotation ;
extern double integralConstantForRotation ;
extern double differentialConstantForRotation ;
extern int maxIntegralValueForRotation ;
extern int maxOutputSpeedForRotation ;
extern int minOutputSpeedForRotation ;
extern double degreeAccuracyForRotation ;
extern double speedAccuracyForRotation ;
extern double integralNewPointForRotation ;
extern bool doPIDForRotation ;
extern float degreesToRotateForRotation ;
extern double bnoSetpointForRotation ;
extern double bnoOffsetForRotation ;
extern double errorForRotation ;
extern double previousIntegralForRotation ;
extern double previouserrorForRotation ;
extern double previousmessungForRotation ;
extern double differenceMeasurementForRotation ;
extern double currentRotationForRotation ;
extern double outputSpeedForRotation ;
extern bool doDrivePID ;
extern double bnoSetpointForDrive ;
extern double bnoOffsetForDrive ;
extern double errorForDrive ;
extern double previousErrorForDrive ;
extern double integralForDrive ;
extern double previousIntegralForDrive ;
extern double proportionalForDrive ;
extern double maxIntegralValueForDrive ;
extern double maxOutputValueDifferenceForDrive ;
extern double integralNewPointForDrive ;
extern double integralConstantForDrive ;
extern double proportionalConstantForDrive ;
extern char victimType;


/*
GlobalMethods
*/

/*void setUpRobot();
void processSwitchInputs();
void processButtonInputs();
void processVLTofInputs();
void processLanbaoTofInputs();
void processColorInput();
*/
void calcBNOCalbHeading();
void calcBNOCalbPitch();

/*void processBnoInputs();*/

/*void processImageInputs();

void processImageOutputs();*/

void resetDrivePID();

float updateAngleTarget(float rotationDegrees);

double atanInDegrees(double d);

void calculateVictim(char victimAsChar);

double calculateDegreeOffset(uint8_t dist1, uint8_t dist2, int distanceBetweenTofs);

float calcDegreesToRotate();

bool hasWallWithinReasonableDistance(uint16_t distance, uint16_t correctionToPlateEdge);

int getAmountOfTilesWithinReasonableDistance(uint16_t distance, uint16_t correctionToPlateEdge);

uint8_t calcDistanceFromPlateEdge(uint16_t distance, uint16_t correctionToPlateEdge);
bool isAbout(float toCompare1, float toCompare2, float tolerance);

char translatePlateTypeToChar(plateTypes plateType);

bool hasWall(uint8_t dist1, uint8_t dist2, bool isSensorValueUsable1, bool isSensorValueUsable2);

uint8_t getDistance(uint8_t dist1, uint8_t dist2, bool isSensorValueUsable1, bool isSensorValueUsable2);

float calcAngleToRotateForCorrection(int errorToWall);

int calcErrorToWall(int frontDistance, int backDistance, int targetDistance);
void resetLast100PitchValues();

float getMeanOfLast100BnoPitches();

#endif