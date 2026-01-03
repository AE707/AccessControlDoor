#include "RFIDDoorAccess.h"

MFRC522 mfrc522(SS_PIN, RST_PIN);

int buttonState = 0;
int buttonState1 = 0;

void setupHardware() {
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_BUTTON1, INPUT);
  Serial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Put your card to the reader...");
  Serial.println();
}

void checkRFID() {
  buttonState = digitalRead(PIN_BUTTON);
  buttonState1 = digitalRead(PIN_BUTTON1);

  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  Serial.print("UID tag :");
  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();

  if (content.substring(1) == "33 D9 C0 0E") {
    delay(2000);
    handleAccessGranted(buttonState == LOW);
  } else {
    handleAccessDenied();
  }
}

void handleAccessGranted(bool buttonState) {
  if (buttonState == HIGH) {
    digitalWrite(PIN_LED_GREEN, HIGH);
    tone(PIN_BUZZER, 1000, 500);
    delay(400);
    digitalWrite(PIN_LED_GREEN, LOW);
    buttonState == LOW ; 
    Serial.println("Authorized access");
    Serial.println("Door open ");
    Serial.println("event saved and insert in table event ");
    delay(400);
  } else {
    digitalWrite(PIN_LED_RED, HIGH);
    tone(PIN_BUZZER, 500, 500);
    Serial.println("Door did not open check service ");
    Serial.println("event saved and insert in table event ");
    delay(400);
    digitalWrite(PIN_LED_RED, LOW);
  }
}

void handleAccessDenied() {
  digitalWrite(PIN_LED_RED, HIGH);
  tone(PIN_BUZZER, 500, 500); // 500 Hz frequency, 500 ms duration
  Serial.println("Access denied");
  Serial.println("Door closed..");
  Serial.println("event saved and insert in table event ");
  delay(400);
  digitalWrite(PIN_LED_RED, LOW);
}
