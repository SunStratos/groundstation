#include "imu.h"
#include "gps.h"
#include "dataLog.h"
#include "accel.h"
#include "LIS3.h"

int timeLimit = 60;
int timeCurr;

void setup()
{
    Serial.begin(115200);
    while(!Serial);

    //imuSetup();
    //gpsSetup();
    MagSetup();

    //smtSDSetup(0);

    timeCurr = millis();
}

void loop()
{
    if (timeCurr >= timeLimit*1000)
    {
        Serial.println("Time limit reached, closing program.");
        while(true);
    }

    unsigned long preLogTime = micros();

    data.timeStamp = micros();

    imuGetData();
    data.temp = imuData.temp;
    data.accX = imuData.accelX;
    data.accY = imuData.accelY;
    data.accZ = imuData.accelZ;
    data.gyrX = imuData.gyroX;
    data.gyrY = imuData.gyroY;
    data.gyrZ = imuData.gyroZ;

    //gpsGetData();
    data.gpsLat = 1.0;// gpsData.latitude;
    data.gpsLon = 1.0;//gpsData.longitude;
    data.gpsAlt = 1.0;//gpsData.altitude;
    data.gpsSat = 1.0;//gpsData.satellites;

    MagGetData();
    data.magX = MagData.MagX;
    data.magY = MagData.MagY;
    data.magZ = MagData.MagZ;

    AccelGetData();
    data.adxlX = AccelData.AccelX;
    data.adxlY = AccelData.AccelY;
    data.adxlZ = AccelData.AccelZ;

    unsigned long postLogTime = micros();

    Serial.printf("Log time (us): %d\t IMU temp: %f\t IMU accel: %f,%f,%f\t IMU gyro: %f,%f,%f,\n GPS: %f,%f,%f,%f\t Mag: %f,%f,%f\t ADXL: %f,%f,%f\n\n", data.timeStamp, data.temp, data.accX, data.accY, data.accZ, data.gyrX, data.gyrY, data.gyrZ, data.gpsAlt, data.gpsLat, data.gpsLon, data.gpsSat, data.magX, data.magY, data.magZ, data.adxlX, data.adxlY, data.adxlZ);
    delay(100);

    timeCurr = millis();
}