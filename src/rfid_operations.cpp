#include "rfid_operations.h"

RFIDOperations::RFIDOperations(int txPin, int rxPin) : mySerial(txPin, rxPin) {
    mySerial.begin(115200);
    
}

void RFIDOperations::begin() {
    mySerial.begin(115200);
}

void RFIDOperations::readCard() {
    if (mySerial.available() > 0) {
        char data[10];
        mySerial.readBytes(data, 10);
        printData(data);
    }
}

void RFIDOperations::printData(char* data) {
    for (int i = 0; i < 10; i++) {
        Serial.print(data[i], HEX);
        Serial.print(" ");
    }
    Serial.println();
}

void RFIDOperations::calculateChecksum(char* data) {
    int checksum = 0;
    for (int i = 0; i < 10; i++) {
        checksum ^= data[i];
    }
    Serial.println(checksum, HEX);
}