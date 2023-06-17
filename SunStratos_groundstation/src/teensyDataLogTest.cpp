#include "dataLog.h"

int timeLimit = 15;
int timeCurr;\

void setup()
{
    Serial.begin(115200);
    while(!Serial);

    teensySDSetup(0, true);

    timeCurr = millis();
}

void loop()
{
    if (timeCurr >= timeLimit*1000)
    {
        Serial.println("Time limit reached, closing program.");
        fileTNS.close();
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

    size_t sizeCurr = rbTNS.bytesUsed();

    if ((sizeCurr + fileTNS.curPosition()) > (LOG_FILE_SIZE - 20))
    {
        Serial.println("File full - quitting.");
        fileTNS.close();
        while(true);
    }

    if (sizeCurr >= 512 && !fileTNS.isBusy()) 
    {
        // Not busy only allows one sector before possible busy wait.
        // Write one sector from RingBuf to file.
        if (512 != rbTNS.writeOut(512)) 
        {
            Serial.println("writeOut failed");
            while(true);
        }
    }

    rbTNS.printf("%llu,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
        data.timeStamp,
        data.temp, data.accX, data.accY, data.accZ,
        data.gyrX, data.gyrY, data.gyrZ,
        data.gpsLat, data.gpsLon, data.gpsAlt, data.gpsSat,
        data.adxlX, data.adxlY, data.adxlZ,
        data.magX, data.magY, data.magZ
    );
    rbTNS.println();

    if (rbTNS.getWriteError()) 
    {
        // Error caused by too few free bytes in RingBuf.
        Serial.println("WriteError");
        while(1);
    }

    rbTNS.sync();
    fileTNS.truncate();

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

    delay(1000);
    timeCurr = millis();
}
