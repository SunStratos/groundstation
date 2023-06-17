//Header file for LoRa
/*
#ifndef LoRa
#define LoRA

#include <RadioLib.h>
#include <dht.h>
#include "dataLog.h"

byte byteArrR[52];

struct DataLogStruct{
    u_int64_t timeStamp;

    // ICM20649 
    float temp;
    float accX;
    float accY;
    float accZ;
    float gyrX;
    float gyrY;
    float gyrZ;

    // Ultimate GPS 
    float gpsLat;
    float gpsLon;
    float gpsAlt;
    float gpsSat;

    // ADXL375 
    float adxlX;
    float adxlY;
    float adxlZ;

    // LIS3MDL 
    float magX;
    float magY;
    float magZ;
};

extern DataLogStruct dataR;

void ByteArrayFormat();

int LoraRSetup();

int LoraReceive();

#endif

*/