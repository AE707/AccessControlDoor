#ifndef RFID_DOOR_ACCESS_H
#define RFID_DOOR_ACCESS_H

#include <SPI.h>
#include <MFRC522.h>
#include <Arduino.h>

// Pin definitions
#define SS_PIN 5
#define RST_PIN 22
#define PIN_LED_GREEN 13
#define PIN_LED_RED 12
#define PIN_BUZZER 14
#define PIN_BUTTON 33 
#define PIN_BUTTON1 27

void setupHardware();
void checkRFID();
void handleAccessGranted(bool buttonState);
void handleAccessDenied();

#endif // RFID_DOOR_ACCESS_H
