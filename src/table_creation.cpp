#include "db_operations.h"
#include <Arduino.h>

void createPuceTable(sqlite3 *db1) {
    int tableExists;
    char* zErrMsg;
    int rc = sqlite3_exec(db1, "SELECT count(*) FROM sqlite_master WHERE type='table' AND name='puce';", queryResultCallback, &tableExists, &zErrMsg);
    if (rc != SQLITE_OK) {
        Serial.printf("Error executing SQL query: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db1);
        return;
    } else {
        Serial.printf("Table exists (1 -> yes / 0 -> no): %i\n", tableExists);
        if (!tableExists) {
            Serial.println("The puce table does not exist yet.");
            rc = db_exec(db1, "CREATE TABLE puce (id_puce INTEGER PRIMARY KEY NOT NULL, statut TEXT NOT NULL, Alias TEXT NOT NULL, Date_expiration DATE NOT NULL, Id_utilisateur INTEGER NOT NULL, date_added DATE DEFAULT CURRENT_DATE)");
            if (rc != SQLITE_OK) {
                sqlite3_close(db1);
                return;
            }
            Serial.println("Table puce created successfully");
        }
        Serial.println("The puce table exists.");
    }
}

void createTimeZoneTable(sqlite3 *db1) {
    int tableExists;
    char* zErrMsg;
    int rc = sqlite3_exec(db1, "SELECT count(*) FROM sqlite_master WHERE type='table' AND name='time_zone';", queryResultCallback, &tableExists, &zErrMsg);
    if (rc != SQLITE_OK) {
        Serial.printf("Error executing SQL query: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db1);
        return;
    } else {
        Serial.printf("Table exists (1 -> yes / 0 -> no): %i\n", tableExists);
        if (!tableExists) {
            Serial.println("The time_zone table does not exist yet.");
            rc = db_exec(db1, "CREATE TABLE time_zone (id INTEGER PRIMARY KEY NOT NULL, start_time TIME NOT NULL, end_time TIME NOT NULL, day_of_week INTEGER NOT NULL)");
            if (rc != SQLITE_OK) {
                sqlite3_close(db1);
                return;
            }
            Serial.println("Table time_zone created successfully");
        }
        Serial.println("The time_zone table exists.");
    }
}

void createEventTable(sqlite3 *db1) {
    int tableExists;
    char* zErrMsg;
    int rc = sqlite3_exec(db1, "SELECT count(*) FROM sqlite_master WHERE type='table' AND name='event';", queryResultCallback, &tableExists, &zErrMsg);
    if (rc != SQLITE_OK) {
        Serial.printf("Error executing SQL query: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db1);
        return;
    } else {
        Serial.printf("Table exists (1 -> yes / 0 -> no): %i\n", tableExists);
        if (!tableExists) {
            Serial.println("The event table does not exist yet.");
            rc = db_exec(db1, "CREATE TABLE event (id INTEGER PRIMARY KEY NOT NULL, puce_id INTEGER NOT NULL, event_type INTEGER NOT NULL, event_time DATETIME NOT NULL)");
            if (rc != SQLITE_OK) {
                sqlite3_close(db1);
                return;
            }
            Serial.println("Table event created successfully");
        }
        Serial.println("The event table exists.");
    }
}

void createSystemSettingTable(sqlite3 *db1) {
    int tableExists;
    char* zErrMsg;
    int rc = sqlite3_exec(db1, "SELECT count(*) FROM sqlite_master WHERE type='table' AND name='system_setting';", queryResultCallback, &tableExists, &zErrMsg);
    if (rc != SQLITE_OK) {
        Serial.printf("Error executing SQL query: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db1);
        return;
    } else {
        Serial.printf("Table exists (1 -> yes / 0 -> no): %i\n", tableExists);
        if (!tableExists) {
            Serial.println("The system_setting table does not exist yet.");
            rc = db_exec(db1, "CREATE TABLE system_setting (id INTEGER PRIMARY KEY NOT NULL, setting_name TEXT NOT NULL, setting_value TEXT NOT NULL)");
            if (rc != SQLITE_OK) {
                sqlite3_close(db1);
                return;
            }
            Serial.println("Table system_setting created successfully");
        }
        Serial.println("The system_setting table exists.");
    }
}

void createStateTable(sqlite3 *db1) {
    int tableExists;
    char* zErrMsg;
    int rc = sqlite3_exec(db1, "SELECT count(*) FROM sqlite_master WHERE type='table' AND name='state';", queryResultCallback, &tableExists, &zErrMsg);
    if (rc != SQLITE_OK) {
        Serial.printf("Error executing SQL query: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db1);
        return;
    } else {
        Serial.printf("Table exists (1 -> yes / 0 -> no): %i\n", tableExists);
        if (!tableExists) {
            Serial.println("The state table does not exist yet.");
            rc = db_exec(db1, "CREATE TABLE state (id INTEGER PRIMARY KEY NOT NULL, state_name TEXT NOT NULL, state_code TEXT NOT NULL)");
            if (rc != SQLITE_OK) {
                sqlite3_close(db1);
                return;
            }
            Serial.println("Table state created successfully");
        }
        Serial.println("The state table exists.");
    }
}