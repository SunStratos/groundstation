#include "gps.h"
#include "imu.h"
#include "accel.h"
#include "LIS3.h"
#include "dataLog.h"
#include "LoRa.h"

void systemsTest();
void testController();

bool launched = false;
int counter = 0;

void setup()
{
    Serial.begin(9600);
    while (!Serial);

    Serial.printf("---------- INITIALISING SYSTEMS ----------\n\n");

    // Initializing sensors
    gpsSetup();
    imuSetup();
    // AccelSetup(); - Redundant
    MagSetup();

    // Initializing SMT SD card and LoRa
    unsigned long long timeStamp = micros();
    smtSDSetup(timeStamp, true);
    LoraSetup();

    Serial.printf("---------- SYSTEMS INITIALISED ----------\n\n");
    testController();

    systemsTest();
}

void loop()
{
    unsigned long start = millis();
    unsigned long long timeStamp = (unsigned long long)time(NULL);

    // Get GPS data every 200ms (5 Hz)
    if (counter % 2 == 0)
    {
        gpsGetData();
        data.gpsLat = gpsData.latitude;
        data.gpsLon = gpsData.longitude;
        data.gpsAlt = gpsData.altitude;
        data.gpsSat = gpsData.satellites;
    }

    imuGetData();
    data.temp = imuData.temp;
    data.accX = imuData.accelX;
    data.accY = imuData.accelY;
    data.accZ = imuData.accelZ;
    data.gyrX = imuData.gyroX;
    data.gyrY = imuData.gyroY;
    data.gyrZ = imuData.gyroZ;

    AccelGetData();
    data.adxlX = AccelData.AccelX;
    data.adxlY = AccelData.AccelY;
    data.adxlZ = AccelData.AccelZ;

    MagGetData();
    data.magX = MagData.MagX;
    data.magY = MagData.MagY;
    data.magZ = MagData.MagZ;

    data.timeStamp = timeStamp;

    // Check if rocket has launched
    if (data.accY > 15 && !launched)
    {
        launched = true;
    }
    // Check if rocket has landed, transfer data to Teensy SD if it has
    else if (data.accY < 1 && launched)
    {
        launched = false;
        transferData();
    }
    // Log data to SMT SD every 200ms (5 Hz)
    else if (counter % 2 == 0)
    {
        logData();
    }

    // Tranmit data every 200 ms (5 Hz) - Not sure if we wanna transmit faster or slower
    if (counter % 2 == 0)
    {
        
    }

    counter++;

    // Ensuring that the loop takes 100ms
    unsigned long end = millis();
    if (end - start < 100)
    {
        delayMicroseconds(100 - (end - start));
    }
}

void systemsTest()
{
    Serial.printf("---------- STARTING SYSTEMS TEST ----------\n\n");

    Serial.println("Timestamp Test (1 Second): ");
    for (int i = 0; i < 10; i++)
    {
        unsigned long long timeStamp = (unsigned long long)time(NULL);
        Serial.printf("UNIX Time: %llu", timeStamp);
        delay(100);
    }
    Serial.println("Timestamp Test Complete!");
    testController();

    Serial.println("GPS Test (Until First Fix): ");
    while(!GPS.fix){
        gpsGetData();
        Serial.println("GPS Data: ");
        Serial.printf("Altitude - %f    Longitude - %f   Latitude - %f   Satellites - %f",
                    gpsData.altitude, gpsData.longitude, gpsData.latitude, gpsData.satellites);
    }
    Serial.println("GPS Test Complete!");
    testController();

    Serial.println("IMU Test (10 Seconds): ");
    for (int i = 0; i < 100; i++)
    {
        imuGetData();
        Serial.println("IMU Data: ");
        Serial.printf("Temperature - %f     Accel (x, y, z) - %f, %f, %f   Gyro (x, y, z) - %f, %f %f",
                    imuData.temp, imuData.accelX, imuData.accelY, imuData.accelZ, imuData.gyroX, imuData.gyroY, imuData.gyroZ);
        delay(100);
    }
    Serial.println("IMU Test Complete!");
    testController(); 

    Serial.println("Accelerometer Test (10 Seconds): ");
    for (int i = 0; i < 100; i++)
    {
        AccelGetData();
        Serial.println("Accelerometer Data: ");
        Serial.printf("Accel (x, y, z) - %f, %f, %f",
                    AccelData.AccelX, AccelData.AccelY, AccelData.AccelZ);
        delay(100);
    }
    Serial.println("Accelerometer Test Complete!");
    testController();

    Serial.println("Magnetometer Test (10 Seconds): ");
    for (int i = 0; i < 100; i++)
    {
        MagGetData();
        Serial.println("Magnetometer Data: ");
        Serial.printf("Mag (x, y, z) - %f, %f, %f",
                    MagData.MagX, MagData.MagY, MagData.MagZ);
        delay(100);
    }
    Serial.println("Magnetometer Test Complete!");
    testController();

    Serial.println("---------- SYSTEMS TEST COMPLETE ----------\n");
}

void testController(){
  Serial.printf("\nPress Enter to continue");
  while (!Serial.available());
  Serial.println();
}
