#include "dataLog.h"

int timeLimit = 15;
int timeCurr;

void setup()
{
    Serial.begin(115200);
    while(!Serial);

    smtSDSetup(0, true);

    timeCurr = millis();
}

void loop()
{
    if (timeCurr >= timeLimit*1000)
    {
        Serial.println("Time limit reached, closing program.");
        fileSMT.close();
        while(true);
    }

    unsigned long preLogTime = micros();

    data.timeStamp = micros();

    data.temp = 10;
    data.accX = 15;
    data.accY = 25;
    data.accZ = 20;
    data.gyrX = 10;
    data.gyrY = 7;
    data.gyrZ = 8;

    data.magX = 5;
    data.magY = 5;
    data.magZ = 5;

    data.gpsAlt = 150;
    data.gpsLat = 2009;
    data.gpsLon = 34762;
    data.gpsSat = 7;

    data.adxlX = 0.5;
    data.adxlY = 30;
    data.adxlZ = 0.7;

    logData();

    unsigned long postLogTime = micros();

    Serial.printf("Log time (us): %d\n", postLogTime - preLogTime);
    Serial.printf("%llu,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n",
            data.timeStamp,
            data.temp, data.accX, data.accY, data.accZ,
            data.gyrX, data.gyrY, data.gyrZ,
            data.gpsLat, data.gpsLon, data.gpsAlt, data.gpsSat,
            data.adxlX, data.adxlY, data.adxlZ,
            data.magX, data.magY, data.magZ
        );

    timeCurr = millis();
}
