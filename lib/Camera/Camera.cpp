#include "Camera.h"

bool CAMERA::handleTimeout(bool isBegin, uint32_t timeout){
    if(isBegin){
        timeoutStartTime = millis();
    }  
    if(millis()-timeoutStartTime > TIMEOUT){
        displayError("Camera has timeouted", FATAL);
        isDisabled = true;
        return true;
    }
    return false;
}

void CAMERA::init(CameraSerial *serial)
{
    this->serial = serial;
    this->serial->begin(BAUD);
}

bool CAMERA::hasData()
{   
    bool hasData = this->serial->available() > 0;
    if(hasData){
        this->enable();
        return hasData;
    }
    if(handleTimeout(false, this->isDisabled?100:TIMEOUT))
        return true;
    return hasData;
}
bool CAMERA::requestIsCompleted() 
{
    return this->hasData();
}
char CAMERA::getVictim()
{   
    if (!this->hasData()) {
        if(this->isDisabled){
            return 'D';
        }else {
            return 'X';
        }
    }
    if(!this->isDisabled)
        return this->serial->readString(4).charAt(2); // Char at 2 is the victim letter wich the camera sends
    return 'D';
}

bool CAMERA::resetCamera(bool sendReset)
{   
    if(handleTimeout(sendReset, this->isDisabled?100:TIMEOUT))
        return true;
    if (sendReset)
    {
        this->serial->clear();
        this->serial->write(RESET_CAMERA);
        return false;
    }
    else
        return hasData();
}
bool CAMERA::stopScanningAndRequestVictim(bool sendRequest)
{
    if(handleTimeout(sendRequest, this->isDisabled?100:TIMEOUT)){
        return true;
    }
    if (sendRequest)
    {
        this->serial->clear();
        this->serial->write(STOP_SCANNING_AND_REQUEST_VICTIMTYPE);
    }
    return this->requestIsCompleted();
}
void CAMERA::startScanning()
{
    this->serial->clear();
    this->serial->write(START_SCANNING);
}
void CAMERA::enable(){
    this->isDisabled = false;
}