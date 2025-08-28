#include "neopixel_utils.h"
#include "sdutils.h"
#include <Adafruit_GPS.h>
#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <SD.h>

#define SD_CARD_CS_PIN 12

#define GPSSerial Serial1

Adafruit_GPS GPS(&GPSSerial);
char gpsBuffer[256] = "";
uint8_t gpsBufferIndex;

enum NMEAPrefix {
    RMC,
    GGA,
    UNKNOWN,
};

NMEAPrefix getNMEAPrefix();

void setup() {
    Serial.begin(115200);
    delay(1000);

    GPS.begin(9600);

    GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
    GPS.sendCommand(PMTK_SET_NMEA_UPDATE_5HZ);

    gpsBufferIndex = 0;
}

void loop() {
    char c;
    if (GPSSerial.available()) {
        c = GPSSerial.read();
        gpsBuffer[gpsBufferIndex] = c;

        if (c == '\n') {
            switch (getNMEAPrefix()) {
            case RMC:
                Serial.printf("%s", gpsBuffer);
                break;
            }

            strncpy(gpsBuffer, "", 256);
            c = '\0';
            gpsBufferIndex = 0;
            return;
        }

        gpsBufferIndex += 1;
    }
}

NMEAPrefix getNMEAPrefix() {
    char buf[4] = "";

    // NMEA sentence starts with $[2 char showing source][3 char showing type]
    if (strlen(gpsBuffer) < 6) {
        return UNKNOWN;
    }

    strncpy(buf, gpsBuffer + 3, 3);
    buf[3] = '\0'; // This needs to be there to make this a valid string

    if (strcmp(buf, "RMC") == 0) {
        return RMC;
    } else if (strcmp(buf, "GGA") == 0) {
        return GGA;
    }

    return UNKNOWN;
}