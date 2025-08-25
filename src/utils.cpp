#include "utils.h"

/*
Starts up with a delay in order to give time for the serial
monitor to connect
*/
void startup() {
    pinMode(LED_BUILTIN, OUTPUT);

    digitalWrite(LED_BUILTIN, HIGH);
    delay(5000);
    Serial.begin(115200);
}