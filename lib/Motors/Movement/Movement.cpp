#include "Movement.h"


Movement::Movement(Motor &motor, sensors_vec_t &orientation, sensors_vec_t &acceleration): motors(&motor){ //Benutzt "Member Initializer List"-Technik ("motors = &motor")
    this->orientation = &orientation;
    this->acceleration = &acceleration;
}

void Movement::process(){
    offGoal = goalAngle - orientation->heading;

    if(movementControl != manuel){
        short sideSpeed = goalAngle * turnSpeed;
        motors[FrontLeft].speed = sideSpeed; 
        motors[BackLeft].speed = sideSpeed;
        motors[FrontRight].speed = -sideSpeed;
        motors[BackRight].speed = -sideSpeed;
        if(abs(goalAngle) <= offsetTreshhold){ //Falls ungefähr richtige Richtung => fahre vorwährts
            motors[FrontLeft].speed += speed; 
            motors[BackLeft].speed += speed;
            motors[FrontRight].speed += speed;
            motors[BackRight].speed += speed;
        }
        for(int i = 0;i<4; i++){
            motors[i].processOutput();
        }
    }
}

void Movement::Stop(int  time){
    motors[0].speed = 0;
    motors[1].speed = 0;
    motors[2].speed = 0;
    motors[3].speed = 0;
    motors[0].processOutput();
    motors[1].processOutput();
    motors[2].processOutput();
    motors[3].processOutput();
    delay(time);
}

void Movement::TurnRight(int Speed){
    //-> this bnoData = &bnoData;

    //float RoboHeading = orientation->roll;
    
            motors[0].speed = Speed;
            motors[1].speed = Speed;
            motors[2].speed = - Speed;
            motors[3].speed = - Speed;
            motors[0].processOutput();
            motors[1].processOutput();
            motors[2].processOutput();
            motors[3].processOutput();
            delay(10);
            //Stop(1);

    
    
}
void Movement::TurnLeft(int Speed){

            motors[0].speed = -Speed;
            motors[1].speed = -Speed;
            motors[2].speed =  Speed;
            motors[3].speed =  Speed;
            motors[0].processOutput();
            motors[1].processOutput();
            motors[2].processOutput();
            motors[3].processOutput();

}

bool Movement::doFrontCorrection(uint8_t currentFrontDistance){ //Copied from Dogs
    if(!hasWallFront || bnoCalbPitch>5 || bnoCalbPitch<-5)
        return true;
    if (currentFrontDistance > (PERFECT_FRONT_DISTANCE + MAX_FRONT_DISTANCE_ERROR))
    {
        this->speed = 30;
        this->goalAngle = this->orientation->heading;
        return false;
    }
    if (currentFrontDistance < (PERFECT_FRONT_DISTANCE - MAX_FRONT_DISTANCE_ERROR))
    {
        this->speed = -30;
        this->goalAngle = this->orientation->heading;
        return false;
    }
    this->speed = 0;
    return true;
}
bool Movement::doBackCorrection(uint8_t currentBackDistance) {
    if (currentBackDistance < (PERFECT_BACK_DISTANCE - MAX_BACK_DISTANCE_ERROR))
    {
        this->speed = 30;
        this->goalAngle = this->orientation->heading;
        return false;
    }
    if (currentBackDistance > (PERFECT_BACK_DISTANCE + MAX_BACK_DISTANCE_ERROR))
    {
        this->speed = -30;
        this->goalAngle = this->orientation->heading;
    }
    this->speed = 0;
    return true;
}
bool Movement::rotateDegreesWithPID(float degrees, bool stepChanged) {
    if (!doPIDForRotation)
    {
        //Serial.println(degrees);
        if (!stepChanged) {
            this->speed = 0;
            this->drive(forward);
            doPIDForRotation = false;
            disableVlTofs = false;
            disableColorSensor = false;
            disableLanbaoTofs = false;
            disableDisplay = false;
            return true;
        }
        degreesToRotateForRotation = -degrees;
        doPIDForRotation = true;
        currentRotationForRotation = 0;
        previousIntegralForRotation = 0;
        previouserrorForRotation = 0;
        outputSpeedForRotation = 0;
        bnoOffsetForRotation = 0;
        previousmessungForRotation = 0;
        errorForRotation = 0;
        bnoSetpointForRotation = robotHeading;
        differenceMeasurementForRotation = 0;
        disableVlTofs = true;
        disableColorSensor = true;
        disableLanbaoTofs = true;
        disableDisplay = true;
    }
    bnoOffsetForRotation = bnoSetpointForRotation - robotHeading;
    differenceMeasurementForRotation = bnoOffsetForRotation - previousmessungForRotation;

    if (differenceMeasurementForRotation > 180 || differenceMeasurementForRotation < -180)
    {
        differenceMeasurementForRotation = bnoOffsetForRotation < previousmessungForRotation ? (bnoOffsetForRotation + 360) - previousmessungForRotation : bnoOffsetForRotation - (previousmessungForRotation + 360);
    }
    currentRotationForRotation += differenceMeasurementForRotation;
    errorForRotation = degreesToRotateForRotation - currentRotationForRotation;

    // Ende des PID
    if ((errorForRotation > -degreeAccuracyForRotation && errorForRotation < degreeAccuracyForRotation) && outputSpeedForRotation < speedAccuracyForRotation && outputSpeedForRotation > -speedAccuracyForRotation)
    {
        this->speed = 0;
        doPIDForRotation = false;
        disableVlTofs = false;
        disableColorSensor = false;
        disableLanbaoTofs = false;
        disableDisplay = false;
        return true;
    }
    // PID Main
    else
    {
        
        double proportional = proportionalConstantForRotation * errorForRotation;
        double integral = max(min((previousIntegralForRotation + 0.5f * integralConstantForRotation * (errorForRotation + previouserrorForRotation) / 1000), maxIntegralValueForRotation), -maxIntegralValueForRotation);
        double differential = differentialConstantForRotation * (differenceMeasurementForRotation);

        outputSpeedForRotation = max(min((proportional + integral + differential), maxOutputSpeedForRotation), -maxOutputSpeedForRotation);

        previousIntegralForRotation = ((errorForRotation > 0 && integral < 0) || (errorForRotation < 0 && integral > 0)) ? ((errorForRotation > 0) ? integralNewPointForRotation : -integralNewPointForRotation) : integral;
        previouserrorForRotation = errorForRotation;
    }
    previousmessungForRotation = bnoOffsetForRotation;
    
    this->speed = outputSpeedForRotation < 0 ? max(minOutputSpeedForRotation, outputSpeedForRotation * (-1) ) : max(minOutputSpeedForRotation, outputSpeedForRotation);
    this->rotate(outputSpeedForRotation < 0 ? LEFT : RIGHT);
    return false;
}

void Movement::ForwardOneTile(int speed){
    motors[0].speed = speed;
    motors[1].speed = speed;
    motors[2].speed = speed;
    motors[3].speed = speed;
    
    motors[0].processOutput();
    motors[1].processOutput();
    motors[2].processOutput();
    motors[3].processOutput();
    delay(ForwardDuration/speed);
}


