#ifndef NEOPIXEL_UTILS
#define NEOPIXEL_UTILS

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

extern Adafruit_NeoPixel neoPixel;

void initializeNeoPixel();

void setNeoPixelColor(int r, int g, int b);

#endif