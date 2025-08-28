#ifndef SDUTILS
#define SDUTILS

#include "utils.h"
#include <Arduino.h>
#include <SD.h>

const uint64_t KIB_BYTES = 1024;
const uint64_t MIB_BYTES = 1048576;

/*
Begins communication with the SDCard using SD.h

Logs either success or failure depending on
*/
boolean mountSDCard(int cs_pin);

/*
Logs the following about the inserted SD card:
    - Type
    - Size
*/
void logSDCardInfo();

#endif