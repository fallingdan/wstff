#include "neopixel_utils.h"
#include "sdutils.h"
#include "utils.h"
#include <Adafruit_DPS310.h>
#include <Adafruit_GPS.h>
#include <Adafruit_ICM20948.h>
#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <SD.h>

#define SD_CARD_CS_PIN 12
#define GPSSerial Serial1

boolean INIT_FAILED = false;

Adafruit_DPS310 DPS;
Adafruit_ICM20948 ICM;
Adafruit_GPS GPS(&GPSSerial);

boolean initializeDPS();
boolean initializeSDCard();
boolean initializeICM();
boolean initializeGPS();

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    initializeNeoPixel();
    setNeoPixelColor(255, 0, 0);

    delay(5000);
    Serial.begin(115200);
    Serial.println("");
    Serial.println("----- Initialization Begin -----");

    // Initialize breakout boards
    initializeDPS();
    initializeICM();
    initializeSDCard();
    initializeGPS();

    digitalWrite(LED_BUILTIN, LOW);
    setNeoPixelColor(0, 255, 0);

    Serial.println("----- Initialization Complete -----");
}

boolean initializeGPS() {
    printHeader("GPS INIT");

    if (!GPS.begin(9600)) {
        Serial.println("\tFailed to initialize GPS");
        return false;
    }

    GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
    Serial.println("\tSet NMEA output to RMC only");

    GPS.sendCommand(PMTK_SET_NMEA_UPDATE_5HZ);
    Serial.println("\tSet NMEA Update rate to 5Hz");

    Serial.println("\tGPS Initialized");

    return true;
}

/*
Start I2C communication with DPS and return
whether it succeeded or failed
*/
boolean initializeDPS() {
    printHeader("DPS310 INIT");

    if (!DPS.begin_I2C()) {
        Serial.println("\tFailed to find DPS");
        Serial.println("\tCheck wiring, connections, and address collisions");
        return false;
    }

    DPS.configurePressure(DPS310_64HZ, DPS310_64SAMPLES);
    Serial.println("\tPressure sample rate: 64Hz, Oversampling Average: 64 Samples");

    DPS.configureTemperature(DPS310_64HZ, DPS310_64SAMPLES);
    Serial.println("\tTemperature sample rate: 64Hz, Oversampling Average: 64 Samples");

    Serial.println("\tDPS Initialized");

    return true;
}
/*
Start I2C communication with ICM and return
whether it succeeded or failed
*/
boolean initializeICM() {
    printHeader("ICM20948 INIT");

    if (!ICM.begin_I2C()) {
        Serial.println("\tFailed to find ICM");
        Serial.println("\tCheck wiring, connections, and address collisions");
        return false;
    }

    ICM.setAccelRange(ICM20948_ACCEL_RANGE_4_G);
    Serial.println("\tSet Acceleration Range: +- 4G");

    ICM.setGyroRange(ICM20948_GYRO_RANGE_500_DPS);
    Serial.println("\tSet Gyro Range: 500 dps (degrees per second)");

    Serial.println("\tICM Initialized");
    return true;
}

/*
Start SPI communication with the SD breakout
and return whether it succeeded or failed
*/
boolean initializeSDCard() {
    printHeader("SD CARD INIT");

    if (!mountSDCard(SD_CARD_CS_PIN)) {
        return false;
    }

    logSDCardInfo();

    Serial.println("\tSD Card Initialized");

    return true;
}

void loop() {
}
