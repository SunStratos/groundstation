 /* #include "LoRaR.h"


#include "Lora.h"

SX1272 lora = new Module(10,2,9,3);

int LoraSetup(){

  int state = lora.begin(868.0);
  if (state == RADIOLIB_ERR_NONE)
  {
    return 0;
  }
    else
    {
    return 1;
    }
}

int LoraReceive(){
    byte byteArr[52];
    int state = lora.receive(byteArr,52);

 if (state == RADIOLIB_ERR_NONE) {
    // packet was successfully received
    Serial.println(F("success!"));

    // print the data of the packet
    ByteArrayFormat(*data,*byteArrR);



    // print the RSSI (Received Signal Strength Indicator)
    // of the last received packet
    Serial.print(F("[SX1272] RSSI:\t\t\t"));
    Serial.print(lora.getRSSI());
    Serial.println(F(" dBm"));

    // print the SNR (Signal-to-Noise Ratio)
    // of the last received packet
    Serial.print(F("[SX1272] SNR:\t\t\t"));
    Serial.print(lora.getSNR());
    Serial.println(F(" dB"));

    // print frequency error
    // of the last received packet
    Serial.print(F("[SX1272] Frequency error:\t"));
    Serial.print(lora.getFrequencyError());
    Serial.println(F(" Hz"));

  } else if (state == RADIOLIB_ERR_RX_TIMEOUT) {
    // timeout occurred while waiting for a packet
    Serial.println(F("timeout!"));

  } else if (state == RADIOLIB_ERR_CRC_MISMATCH) {
    // packet was received, but is malformed
    Serial.println(F("CRC error!"));

  } else {
    // some other error occurred
    Serial.print(F("failed, code "));
    Serial.println(state);

  }
}



union byte_float_union 
{
    byte bytesFromArr[4];
    float floatVal;
};

void ByteArrayFormat(DataRxStruct *data, byte *byteArr)
{
     // GPS latitiude
    byte_float_union dataUnion;
    dataUnion.bytesFromArr[0] = byteArr[0];
    dataUnion.bytesFromArr[1] = byteArr[1];
    dataUnion.bytesFromArr[2] = byteArr[2];
    dataUnion.bytesFromArr[3] = byteArr[3];
    data->gpslat = dataUnion.floatVal;

    // GPS longitude
    dataUnion.bytesFromArr[0] = byteArr[0];
    dataUnion.bytesFromArr[1] = byteArr[1];
    dataUnion.bytesFromArr[2] = byteArr[2];
    dataUnion.bytesFromArr[3] = byteArr[3];
    data->gpslong = dataUnion.floatVal;

    // GPS altitude
    dataUnion.bytesFromArr[0] = byteArr[0];
    dataUnion.bytesFromArr[1] = byteArr[1];
    dataUnion.bytesFromArr[2] = byteArr[2];
    dataUnion.bytesFromArr[3] = byteArr[3];
    data->gpsalt = dataUnion.floatVal;

    // GPS satellites
    dataUnion.bytesFromArr[0] = byteArr[0];
    dataUnion.bytesFromArr[1] = byteArr[1];
    dataUnion.bytesFromArr[2] = byteArr[2];
    dataUnion.bytesFromArr[3] = byteArr[3];
    data->gpssat = dataUnion.floatVal;

    // Accelerometer X
    dataUnion.bytesFromArr[0] = byteArr[0];
    dataUnion.bytesFromArr[1] = byteArr[1];
    dataUnion.bytesFromArr[2] = byteArr[2];
    dataUnion.bytesFromArr[3] = byteArr[3];
    data->accelX = dataUnion.floatVal;

    // Accelerometer Y
    dataUnion.bytesFromArr[0] = byteArr[0];
    dataUnion.bytesFromArr[1] = byteArr[1];
    dataUnion.bytesFromArr[2] = byteArr[2];
    dataUnion.bytesFromArr[3] = byteArr[3];
    data->accelY = dataUnion.floatVal;

    // Accelerometer Z
    dataUnion.bytesFromArr[0] = byteArr[0];
    dataUnion.bytesFromArr[1] = byteArr[1];
    dataUnion.bytesFromArr[2] = byteArr[2];
    dataUnion.bytesFromArr[3] = byteArr[3];
    data->accelZ = dataUnion.floatVal;;

    // Gyroscope X
    dataUnion.bytesFromArr[0] = byteArr[0];
    dataUnion.bytesFromArr[1] = byteArr[1];
    dataUnion.bytesFromArr[2] = byteArr[2];
    dataUnion.bytesFromArr[3] = byteArr[3];
    data->gyroX = dataUnion.floatVal;

    // Gyroscope Y
    dataUnion.bytesFromArr[0] = byteArr[0];
    dataUnion.bytesFromArr[1] = byteArr[1];
    dataUnion.bytesFromArr[2] = byteArr[2];
    dataUnion.bytesFromArr[3] = byteArr[3];
    data->gyroY = dataUnion.floatVal;

    // Gyroscope Z
    dataUnion.bytesFromArr[0] = byteArr[0];
    dataUnion.bytesFromArr[1] = byteArr[1];
    dataUnion.bytesFromArr[2] = byteArr[2];
    dataUnion.bytesFromArr[3] = byteArr[3];
    data->gyroZ = dataUnion.floatVal;

    // Magnetometer X
    dataUnion.bytesFromArr[0] = byteArr[0];
    dataUnion.bytesFromArr[1] = byteArr[1];
    dataUnion.bytesFromArr[2] = byteArr[2];
    dataUnion.bytesFromArr[3] = byteArr[3];
    data->magZ = dataUnion.floatVal;

    // Magnetometer Y
    dataUnion.bytesFromArr[0] = byteArr[0];
    dataUnion.bytesFromArr[1] = byteArr[1];
    dataUnion.bytesFromArr[2] = byteArr[2];
    dataUnion.bytesFromArr[3] = byteArr[3];
    data->magY = dataUnion.floatVal;

    // Magnetometer Z
    dataUnion.bytesFromArr[0] = byteArr[0];
    dataUnion.bytesFromArr[1] = byteArr[1];
    dataUnion.bytesFromArr[2] = byteArr[2];
    dataUnion.bytesFromArr[3] = byteArr[3];
    data->magZ = dataUnion.floatVal;
}

*/