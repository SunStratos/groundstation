//Header file for LoRa

#ifndef LoRa
#define LoRA

#include <RadioLib.h>
#include <dht.h>
#include "dataLog.h"

byte byteArr[52];

void ByteArrayFormat();

int LoraSetup();

int LoraTrans();

#endif