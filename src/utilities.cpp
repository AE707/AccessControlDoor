#include "utilities.h"
#include <Arduino.h>

void getCurrentTime(struct tm *timeinfo) {
    if (!getLocalTime(timeinfo)) {
        Serial.println("Failed to obtain time");
        return;
    }
}