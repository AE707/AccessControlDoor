#include <arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
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
#include "time_zone_operations.h"
#include "LEDControl.h" // Include your LED control library

#define FORMAT_LITTLEFS_IF_FAILED true

WiFiClient espClient;
PubSubClient client(espClient);

const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;

const char* ssid = "Alaa's A34";
const char* password = "1234567890";
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 0;
const int daylightOffset_sec = 3600;
sqlite3 *db1;

void printLocalTime();
void initWiFi();
void initTime();
void initFileSystem();
void initMQTT();
void initDatabase();
void processRFIDData();

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
    processRFIDData();
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
    createStateTable(db1);

    sqlite3_close(db1);
}

void processRFIDData() {
    int num_puce = getRFIDData(); // Function to get RFID data
    char num_state_p[10] = ""; // Initialize state variable

    // Check RFID data and time zone authorization
    sqlite3 *db = initializeDatabase(); // Initialize your SQLite database
    checkPuceVIPStatus(db, num_puce, num_state_p);
    verifyTimeZone(db, num_puce, num_state_p);

    // Control LED signals based on the checks
    if (strcmp(num_state_p, "1000") == 0) {
        // Green LED high for 5 seconds
        turnOnGreenLED();
        delay(5000); // Delay for 5 seconds

        // Red LED high for 2 seconds after 10 seconds
        delay(5000); // Delay for 5 seconds
        turnOffGreenLED();
        turnOnRedLED();
        delay(2000); // Delay for 2 seconds

        // Save data in table_state
        saveStateInTable(db, num_state_p);
    } else {
        // Red LED high for 2 seconds
        turnOnRedLED();
        delay(2000); // Delay for 2 seconds

        // Save state in table_state
        saveStateInTable(db, num_state_p);
    }

    // Close the database connection
    closeDatabase(db);
}