#include "neopixel_utils.h"

void initializeNeoPixel() {
    pixel = Adafruit_NeoPixel(1, PIN_NEOPIXEL, NEO_RGB + NEO_KHZ800);

    pixel.begin();
    pixel.clear();
}

void setPixelColor(int r, int g, int b) {
    pixel.setBrightness(200);
    pixel.setPixelColor(0, r, g, b);
    pixel.show();
}