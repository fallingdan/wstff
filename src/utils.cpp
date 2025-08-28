#include "utils.h"

void printHeader(const char *header) {
    int length = strlen(header);

    for (int i = 0; i < length + 4; i++) {
        Serial.printf("-");
    }
    Serial.print("\n");

    Serial.printf("| %s |\n", header);

    for (int i = 0; i < length + 4; i++) {
        Serial.printf("-");
    }
    Serial.print("\n");
}