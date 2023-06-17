#ifndef DATALOG
#define DATALOG

#include <SPI.h>
#include "SdFat.h"
#include <RingBuf.h>

// SMT SD card attached to SPI bus as follows:
// MOSI - pin 11
// MISO - pin 12
// CLK - pin 13

#define SMT_CS 36
#define TEENSY_SD_CONFIG SdioConfig(FIFO_SDIO)
#define SMT_SD_CONFIG SdSpiConfig(SMT_CS, SHARED_SPI, SD_SCK_MHZ(16))

//#define error(s) sd.errorHalt(&Serial, F(s))

// Log file capacity for over 40 minutes worth of data, sampling at 1 Hz, with 136 byte lines
#define LOG_FILE_SIZE 256*60*40

// Ringbuf capacity for over 800 ms worth of data, sampling at 1 Hz, with 136 byte lines
#define RING_BUF_CAPACITY 800 * 256

extern SdFs sdTNS;
extern FsFile fileTNS;

extern SdFs sdSMT;
extern FsFile fileSMT;

extern RingBuf<FsFile, RING_BUF_CAPACITY> rbTNS;
extern RingBuf<FsFile, RING_BUF_CAPACITY> rbSMT;

extern char fileName[20];
extern char line[70];

struct DataLogStruct{
    u_int64_t timeStamp;

    /** ICM20649 **/
    double temp;
    double accX;
    double accY;
    double accZ;
    double gyrX;
    double gyrY;
    double gyrZ;

    /** Ultimate GPS **/
    double gpsLat;
    double gpsLon;
    double gpsAlt;
    double gpsSat;

    /** ADXL375 **/
    double adxlX;
    double adxlY;
    double adxlZ;

    /** LIS3MDL **/
    double magX;
    double magY;
    double magZ;
};

extern DataLogStruct data;

void teensySDSetup(unsigned long long timeStamp, bool removeFile);

void smtSDSetup(unsigned long long timeStamp, bool removeFile);

void logData();

void transferData();

void readFile();

char* skipSpace(char* str);

bool parseLine(char* str);

#endif 