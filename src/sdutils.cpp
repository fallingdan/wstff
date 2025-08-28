#include "sdutils.h"

void logSDCardType() {
    sdcard_type_t sdCardType = SD.cardType();

    switch (sdCardType) {
    case CARD_NONE:
        Serial.println("\tCard type: NONE");
        break;

    case CARD_MMC:
        Serial.println("\tCard type: MMC");
        break;

    case CARD_SD:
        Serial.println("\tCard type: SD");
        break;

    case CARD_SDHC:
        Serial.println("\tCard type: SDHC");
        break;

    default:
        Serial.println("\tCard type: Unknown");
        break;
    }
}

void logSDCardSize() {
    uint64_t cardSize = SD.cardSize();

    cardSize = cardSize / 1024;
    cardSize = cardSize / 1024;

    Serial.printf("\tCard Size (MiB): %d\n", cardSize);
}

String getBytesFormatted(uint64_t bytes) {
    char buffer[64];

    if (bytes >= KIB_BYTES && bytes < MIB_BYTES) {
        bytes = bytes / 1024;
        sprintf(buffer, "%d KiB", bytes);
    } else if (bytes >= MIB_BYTES) {
        bytes = (bytes / 1024) / 1024;
        sprintf(buffer, "%d MiB", bytes);
    } else {
        sprintf(buffer, "%d bytes", bytes);
    }

    return buffer;
}

void logSDCardRemaining() {
    String usedBytes = getBytesFormatted(SD.usedBytes());
    String totalBytes = getBytesFormatted(SD.totalBytes());

    Serial.printf("\t%s used of %s total\n", usedBytes, totalBytes);
}

void logSDCardInfo() {
    logSDCardType();
    logSDCardSize();
    logSDCardRemaining();
}

boolean mountSDCard(int cs_pin) {
    if (!SD.begin(cs_pin)) {
        Serial.println("\tCard mount failed");
        return false;
    } else {
        Serial.println("\tCard mount successful");
        return true;
    }
}