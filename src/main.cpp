#include "neopixel_utils.h"
#include "sdutils.h"
#include <Arduino.h>
#include <FreeRTOS.h>
#include <SD.h>
#include <task.h>

#define SD_CARD_CS_PIN 12

void neopixel_task(void *pvParameters);
void builtin_task(void *pvParameters);

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    initializeNeoPixel();

    delay(5000);
    Serial.begin(115200);
    Serial.println("");
    Serial.println("----- Initialization Begin -----");

    xTaskCreate(neopixel_task, "NeoPixelTask", 2048, NULL, 5, NULL);
    xTaskCreate(builtin_task, "BuiltinTask", 2048, NULL, 5, NULL);

    // Mount and log info about SD Card
    mountSDCard(SD_CARD_CS_PIN);
    logSDCardInfo();

    Serial.println("----- Initialization Complete -----");
}

void neopixel_task(void *pvParameters) {
    while (1) {
        for (int i = 0; i < 256; i++) {
            setNeoPixelColor(i, 255 - i, 0);
            delay(50);
        }

        for (int i = 0; i < 256; i++) {
            setNeoPixelColor(255 - i, i, 0);
            delay(50);
        }
    }
}

void builtin_task(void *pvParameters) {
    while (1) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);
        digitalWrite(LED_BUILTIN, LOW);
        delay(500);
    }
}

void loop() {
    vTaskDelete(nullptr);
}
