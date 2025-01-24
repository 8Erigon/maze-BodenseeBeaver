#include <Arduino.h>

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
victimTypes victimType;