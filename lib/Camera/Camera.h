#ifndef CAMERA_H
#define CAMERA_H

#include <Arduino.h>
//#include "VarsFromDogs.h"

//Data Transmission Speed
#define BAUD 57600
//Timeout
#define TIMEOUT 2000
//Protocols
#define RESET_CAMERA "C(R)"
#define STOP_SCANNING_AND_REQUEST_VICTIMTYPE "E(D)"
#define START_SCANNING "S(D)"

#if __has_include("CameraSerialSetup.h")
#include "CameraSerialSetup.h"
#else
typedef HardwareSerialIMXRT CameraSerial;
#endif

class CAMERA
{
    public: 
        void init(CameraSerial* serial);
        bool resetCamera(bool sendReset);
        bool stopScanningAndRequestVictim(bool sendRequest);
        void startScanning();
        bool hasData();
        bool requestIsCompleted();
        char getVictim();
        void enable();

    private:
        bool handleTimeout(bool isBegin, uint32_t timeout);
        bool isDisabled = false;
        uint64_t timeoutStartTime = -1;
        CameraSerial* serial;
};

#endif