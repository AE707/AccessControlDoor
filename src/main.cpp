#include <arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "config.h"
#include <SPI.h>
#include <FS.h>
#include "LittleFS.h"
#include <string>
#include <WiFi.h>
#include "time.h"
#include "db_operations.h"
#include <PubSubClient.h>
#include "mqtt_operations.h"
#include "puce_operations.h"
#include <config_ext.h>
#include "table_creation.h"

#define FORMAT_LITTLEFS_IF_FAILED true

WiFiClient espClient;
PubSubClient client(espClient);

sqlite3 *db1;

void printLocalTime();
void initWiFi();
void initTime();
void initFileSystem();
void initMQTT();
void initDatabase();


void setup() {
    Serial.begin(115200);
    initWiFi();
    initTime();
    initFileSystem();
    initMQTT();
    initDatabase();
}

void loop() {
    // Print the local time at the start of each loop iteration
    printLocalTime();

    // Delay for a second to pace the loop execution
    delay(1000);

    // Check if the MQTT client is connected
    if (!client.connected()) {
        Serial.println("Connecting to MQTT...");
        setup_mqtt(client, mqtt_server, mqtt_port);
    }

    // Process incoming messages and maintain MQTT connection
    client.loop();

    

    // Process RFID data
    
}

void printLocalTime() {
    char buf[64];
    struct tm timeinfo;

    if (!getLocalTime(&timeinfo)) {
        Serial.println("Failed to obtain time");
        return;
    }
    
    strftime(buf, sizeof(buf), "%A, %B %d %Y %H:%M:%S", &timeinfo);
    Serial.println(buf);
}

void initWiFi() {
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi connected.");
}

void initTime() {
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    printLocalTime();
}

void initFileSystem() {
    if (!LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED, "/littlefs")) {
        Serial.println("Failed to mount file system");
        return;
    }

    File root = LittleFS.open("/");
    if (!root) {
        Serial.println("- failed to open directory");
        return;
    }
    if (!root.isDirectory()) {
        Serial.println(" - not a directory");
        return;
    }
    File file = root.openNextFile();
    while (file) {
        if (file.isDirectory()) {
            Serial.print("  DIR : ");
            Serial.println(file.name());
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("\tSIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}

void initMQTT() {
    setup_mqtt(client, mqtt_server, mqtt_port);
    mqtt_subscribe(client, "your/topic");
}

void initDatabase() {
    sqlite3_initialize();
    if (!db_open("/littlefs/test.db", &db1)) return;

    createPuceTable(db1);
    createTimeZoneTable(db1);
    createEventTable(db1);
    createSystemSettingTable(db1);
    createJourTable(db1);
    createTimeSlotTable(db1);
    createJourTimeSlotTable(db1);
    createTimezoneJourTimeSlotTable(db1);
    

    sqlite3_close(db1);
}



