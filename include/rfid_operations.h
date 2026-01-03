#ifndef RFID_OPERATIONS_H
#define RFID_OPERATIONS_H

#include <SoftwareSerial.h>

class RFIDOperations {
public:
    RFIDOperations(int txPin, int rxPin);
    void begin();
    void readCard();
    void printData(char* data);
    void calculateChecksum(char* data);

private:
    SoftwareSerial mySerial;
    int txPin;
    int rxPin;
};

#endif