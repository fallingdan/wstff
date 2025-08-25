#include "neopixel_utils.h"

Adafruit_NeoPixel neoPixel = Adafruit_NeoPixel(1, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

void initializeNeoPixel() {
    neoPixel.begin();
    neoPixel.clear();
}

void setNeoPixelColor(int r, int g, int b) {
    neoPixel.setBrightness(100);
    neoPixel.setPixelColor(0, r, g, b);
    neoPixel.show();
}