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


#define FORMAT_LITTLEFS_IF_FAILED true


const char* ssid = "Alaa's A34";
const char* password = "1234567890";
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 0;
const int daylightOffset_sec = 3600;
sqlite3 *db1;

void printLocalTime();

void setup() {
    Serial.begin(115200);
    // Connect to Wi-Fi
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi connected.");
    // Init and get the time
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    printLocalTime();

    if (!LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED, "/littlefs"))
    {
        Serial.println("Failed to mount file system");
        return;
    }

    

    // list LITTLEFS contents
    File root = LittleFS.open("/");
    if (!root)
    {
        Serial.println("- failed to open directory");
        return;
    }
    if (!root.isDirectory())
    {
        Serial.println(" - not a directory");
        return;
    }
    File file = root.openNextFile();
    while (file)
    {
        if (file.isDirectory())
        {
            Serial.print("  DIR : ");
            Serial.println(file.name());
        }
        else
        {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("\tSIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }

    // remove existing file
    LittleFS.remove("/test.db");

    sqlite3_initialize();

    if (!db_open("/littlefs/test.db", &db1))
        return;


    // Database operations
    sqlite3 *db1;
    if (!db_open("/littlefs/test.db", &db1)) return;

    // Create tables if they don't exist
    int tableExists = 0;
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db1, "SELECT count(*) FROM sqlite_master WHERE type='table' AND name='puce';", queryResultCallback, &tableExists, & zErrMsg);
    if (rc != SQLITE_OK) {
        Serial.printf("Error executing SQL query: %s\n", zErrMsg);
        sqlite3_free( zErrMsg);
        sqlite3_close(db1);
        return;
    } else {
        Serial.printf("Table exists (1 -> yes /0 -> no): %i\n", tableExists);
        if (!tableExists) {
            Serial.println("The puce table does not exist yet.");
            rc = db_exec(db1, "CREATE TABLE puce (id_puce INTEGER PRIMARY KEY NOT NULL, statut TEXT NOT NULL, Alias TEXT NOT NULL, Date_expiration DATE NOT NULL, Id_utilisateur INTEGER NOT NULL, date_added DATE DEFAULT CURRENT_DATE)");
            if (rc != SQLITE_OK) {
                sqlite3_close(db1);
                return;
            }
            Serial.println("Table created successfully");
        }
        Serial.println("The puce table exists.");
        rc = db_exec(db1, "INSERT INTO puce (id_puce, statut, Alias, Date_expiration, Id_utilisateur) VALUES (1, 'V', 'Rania_KZ', '2024-04-18', 12345);");
        if (rc != SQLITE_OK) {
            sqlite3_close(db1);
            return;
        }
    }

    sqlite3_close(db1);
}

void loop() {
    printLocalTime();
    delay(1000);
}

void printLocalTime() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        Serial.println("Failed to obtain time");
        return;
    }
    Serial.print(&timeinfo, "%A, %B %d %Y %H:%M:%S");
    Serial.println();
}