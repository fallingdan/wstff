#include "neopixel_utils.h"
#include "sdutils.h"
#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <SD.h>

#define SD_CARD_CS_PIN 12

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    initializeNeoPixel();
    setNeoPixelColor(255, 0, 0);

    delay(5000);
    Serial.begin(115200);
    Serial.println("");
    Serial.println("----- Initialization Begin -----");

    // Mount and log info about SD Card
    mountSDCard(SD_CARD_CS_PIN);
    logSDCardInfo();

    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("----- Initialization Complete -----");

    setNeoPixelColor(0, 255, 0);
}

void loop() {
}
