#ifndef NEOPIXEL_UTILS
#define NEOPIXEL_UTILS

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

Adafruit_NeoPixel pixel;

void initializeNeoPixel();

void setPixelColor(int r, int g, int b);

#endif