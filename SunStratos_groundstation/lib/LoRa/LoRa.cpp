
#include "Lora.h"

SX1272 loraT = new Module(10,2,9,3);

int LoraSetup(){

    
    int state = loraT.begin(868.0);
    if (state == RADIOLIB_ERR_NONE)
    {
        return 1;
    }
        else
    {
        return 0;
    }
  }

int LoraTrans(){

    int state = loraT.transmit(byteArr,52);

    
    if (state == RADIOLIB_ERR_NONE) {
    // the packet was successfully transmitted
    return 0;

  } else if (state == RADIOLIB_ERR_TX_TIMEOUT) {
    // timeout occurred while transmitting packet
    return 1;

  } else {
    // some other error occurred
    return 2;
  }
}



union byte_float_union 
{
    byte bytesFromFloat[4];
    float floatVal;
};

void ByteArrayFormat(DataLogStruct *data, byte *byteArr)
{
     // GPS latitiude
    float latTransmit = static_cast<float>(data->gpsLat);
    byte_float_union latUnion;
    latUnion.floatVal = latTransmit;
    byteArr[1] = latUnion.bytesFromFloat[0];
    byteArr[2] = latUnion.bytesFromFloat[1];
    byteArr[3] = latUnion.bytesFromFloat[2];
    byteArr[4] = latUnion.bytesFromFloat[3];

    // GPS longitude
    float lonTransmit = static_cast<float>(data->gpsLon);
    byte_float_union lonUnion;
    lonUnion.floatVal = lonTransmit;
    byteArr[5] = lonUnion.bytesFromFloat[0];
    byteArr[6] = lonUnion.bytesFromFloat[1];
    byteArr[7] = lonUnion.bytesFromFloat[2];
    byteArr[8] = lonUnion.bytesFromFloat[3];

    // GPS altitude
    float altTransmit = static_cast<float>(data->gpsAlt);
    byte_float_union altUnion;
    altUnion.floatVal = altTransmit;
    byteArr[9] = altUnion.bytesFromFloat[0];
    byteArr[10] = altUnion.bytesFromFloat[1];
    byteArr[11] = altUnion.bytesFromFloat[2];
    byteArr[12] = altUnion.bytesFromFloat[3];

    // GPS satellites
    float satTransmit = static_cast<float>(data->gpsSat);
    byte_float_union satUnion;
    satUnion.floatVal = satTransmit;
    byteArr[13] = satUnion.bytesFromFloat[0];
    byteArr[14] = satUnion.bytesFromFloat[1];
    byteArr[15] = satUnion.bytesFromFloat[2];
    byteArr[16] = satUnion.bytesFromFloat[3];

    // Accelerometer X
    float accXTransmit = static_cast<float>(data->accX);
    byte_float_union accXUnion;
    accXUnion.floatVal = accXTransmit;
    byteArr[17] = accXUnion.bytesFromFloat[0];
    byteArr[18] = accXUnion.bytesFromFloat[1];
    byteArr[19] = accXUnion.bytesFromFloat[2];
    byteArr[20] = accXUnion.bytesFromFloat[3];

    // Accelerometer Y
    float accYTransmit = static_cast<float>(data->accY);
    byte_float_union accYUnion;
    accYUnion.floatVal = accYTransmit;
    byteArr[21] = accYUnion.bytesFromFloat[0];
    byteArr[22] = accYUnion.bytesFromFloat[1];
    byteArr[23] = accYUnion.bytesFromFloat[2];
    byteArr[24] = accYUnion.bytesFromFloat[3];

    // Accelerometer Z
    float accZTransmit = static_cast<float>(data->accZ);
    byte_float_union accZUnion;
    accZUnion.floatVal = accZTransmit;
    byteArr[25] = accZUnion.bytesFromFloat[0];
    byteArr[26] = accZUnion.bytesFromFloat[1];
    byteArr[27] = accZUnion.bytesFromFloat[2];
    byteArr[28] = accZUnion.bytesFromFloat[3];

    // Gyroscope X
    float gyrXTransmit = static_cast<float>(data->gyrX);
    byte_float_union gyrXUnion;
    gyrXUnion.floatVal = gyrXTransmit;
    byteArr[29] = gyrXUnion.bytesFromFloat[0];
    byteArr[30] = gyrXUnion.bytesFromFloat[1];
    byteArr[31] = gyrXUnion.bytesFromFloat[2];
    byteArr[32] = gyrXUnion.bytesFromFloat[3];

    // Gyroscope Y
    float gyrYTransmit = static_cast<float>(data->gyrY);
    byte_float_union gyrYUnion;
    gyrYUnion.floatVal = gyrYTransmit;
    byteArr[33] = gyrYUnion.bytesFromFloat[0];
    byteArr[34] = gyrYUnion.bytesFromFloat[1];
    byteArr[35] = gyrYUnion.bytesFromFloat[2];
    byteArr[36] = gyrYUnion.bytesFromFloat[3];

    // Gyroscope Z
    float gyrZTransmit = static_cast<float>(data->gyrZ);
    byte_float_union gyrZUnion;
    gyrZUnion.floatVal = gyrZTransmit;
    byteArr[37] = gyrZUnion.bytesFromFloat[0];
    byteArr[38] = gyrZUnion.bytesFromFloat[1];
    byteArr[39] = gyrZUnion.bytesFromFloat[2];
    byteArr[40] = gyrZUnion.bytesFromFloat[3];

    // Magnetometer X
    float magXTransmit = static_cast<float>(data->magX);
    byte_float_union magXUnion;
    magXUnion.floatVal = magXTransmit;
    byteArr[41] = magXUnion.bytesFromFloat[0];
    byteArr[42] = magXUnion.bytesFromFloat[1];
    byteArr[43] = magXUnion.bytesFromFloat[2];
    byteArr[44] = magXUnion.bytesFromFloat[3];

    // Magnetometer Y
    float magYTransmit = static_cast<float>(data->magY);
    byte_float_union magYUnion;
    magYUnion.floatVal = magYTransmit;
    byteArr[45] = magYUnion.bytesFromFloat[0];
    byteArr[46] = magYUnion.bytesFromFloat[1];
    byteArr[47] = magYUnion.bytesFromFloat[2];
    byteArr[48] = magYUnion.bytesFromFloat[3];

    // Magnetometer Z
    float magZTransmit = static_cast<float>(data->magZ);
    byte_float_union magZUnion;
    magZUnion.floatVal = magZTransmit;
    byteArr[49] = magZUnion.bytesFromFloat[0];
    byteArr[50] = magZUnion.bytesFromFloat[1];
    byteArr[51] = magZUnion.bytesFromFloat[2];
    byteArr[52] = magZUnion.bytesFromFloat[3];
}