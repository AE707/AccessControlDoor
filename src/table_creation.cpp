#include "db_operations.h"
#include <Arduino.h>
#include <config_ext.h>
#include "table_creation.h"

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
            rc = db_exec(db1, "CREATE TABLE puce (id_puce INTEGER PRIMARY KEY NOT NULL, statut TEXT NOT NULL, Alias TEXT NOT NULL, Date_expiration DATE NOT NULL, Id_utilisateur INTEGER NOT NULL, date_added DATE DEFAULT CURRENT_DATE, id_timezone INTEGER REFERENCES time_zone(id_timezone))");
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
            rc = db_exec(db1, "CREATE TABLE time_zone (id_timezone INTEGER PRIMARY KEY NOT NULL, name string )");
            if (rc != SQLITE_OK) {
                sqlite3_close(db1);
                return;
            }
            Serial.println("Table time_zone created successfully");
        }
        Serial.println("The time_zone table exists.");
    }
}

void createJourTable(sqlite3 *db1) {
    int tableExists;
    char* zErrMsg;
    int rc = sqlite3_exec(db1, "SELECT count(*) FROM sqlite_master WHERE type='table' AND name='jour';", queryResultCallback, &tableExists, &zErrMsg);
    if (rc != SQLITE_OK) {
        Serial.printf("Error executing SQL query: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db1);
        return;
    } else {
        Serial.printf("Table exists (1 -> yes / 0 -> no): %i\n", tableExists);
        if (!tableExists) {
            Serial.println("The jour table does not exist yet.");
            rc = db_exec(db1, "CREATE TABLE jour (id_jour INTEGER PRIMARY KEY NOT NULL, nom_jour string )");
            if (rc != SQLITE_OK) {
                sqlite3_close(db1);
                return;
            }
            Serial.println("Table jour created successfully");
        }
        Serial.println("The jour table exists.");
    }
}

void createTimeSlotTable(sqlite3 *db1) {
    int tableExists;
    char* zErrMsg;
    int rc = sqlite3_exec(db1, "SELECT count(*) FROM sqlite_master WHERE type='table' AND name='time_slot';", queryResultCallback, &tableExists, &zErrMsg);
    if (rc != SQLITE_OK) {
        Serial.printf("Error executing SQL query: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db1);
        return;
    } else {
        Serial.printf("Table exists (1 -> yes / 0 -> no): %i\n", tableExists);
        if (!tableExists) {
            Serial.println("The timeslot table does not exist yet.");
            rc = db_exec(db1, "CREATE TABLE jour (id_timeslot INTEGER PRIMARY KEY NOT NULL, start_time TIME, end_time TIME )");
            if (rc != SQLITE_OK) {
                sqlite3_close(db1);
                return;
            }
            Serial.println("Table timeslot created successfully");
        }
        Serial.println("The timeslot table exists.");
    }
}

void createJourTimeSlotTable(sqlite3 *db1) {
    int tableExists;
    char* zErrMsg;
    int rc = sqlite3_exec(db1, "SELECT count(*) FROM sqlite_master WHERE type='table' AND name='jour_timeslot';", queryResultCallback, &tableExists, &zErrMsg);
    if (rc != SQLITE_OK) {
        Serial.printf("Error executing SQL query: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db1);
        return;
    } else {
        Serial.printf("Table exists (1 -> yes / 0 -> no): %i\n", tableExists);
        if (!tableExists) {
            Serial.println("The jourtimeslot table does not exist yet.");
            rc = db_exec(db1, "CREATE TABLE jour_timeslot (id_jourtimeslot INTEGER PRIMARY KEY NOT NULL , id_jour INTEGER REFERENCES jour(id_jour), id_timezone INTEGER REFERENCES time_zone(id_timezone)  )");
            if (rc != SQLITE_OK) {
                sqlite3_close(db1);
                return;
            }
            Serial.println("Table jourtimeslot created successfully");
        }
        Serial.println("The jourtimeslot table exists.");
    }
}

void createTimezoneJourTimeSlotTable(sqlite3 *db1) {
    int tableExists;
    char* zErrMsg;
    int rc = sqlite3_exec(db1, "SELECT count(*) FROM sqlite_master WHERE type='table' AND name='timezonejour_timeslot';", queryResultCallback, &tableExists, &zErrMsg);
    if (rc != SQLITE_OK) {
        Serial.printf("Error executing SQL query: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db1);
        return;
    } else {
        Serial.printf("Table exists (1 -> yes / 0 -> no): %i\n", tableExists);
        if (!tableExists) {
            Serial.println("The timezonejourtimeslot table does not exist yet.");
            rc = db_exec(db1, "CREATE TABLE jour (id_timezonejourtimeslot INTEGER PRIMARY KEY NOT NULL,  id_jourtimeslot INTEGER REFERENCES jour_timeslot(id_jourtimeslot), id_timezone INTEGER REFERENCES time_zone(id_timezone)  )");
            if (rc != SQLITE_OK) {
                sqlite3_close(db1);
                return;
            }
            Serial.println("Table jourtimeslot created successfully");
        }
        Serial.println("The jourtimeslot table exists.");
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
            rc = db_exec(db1, "CREATE TABLE event (id_event INTEGER PRIMARY KEY NOT NULL DEFAULT (RANDOM()),  id_puce INTEGER REFERENCES puce(id_puce), state INTEGER NOT NULL, date_heure_access DATETIME NOT NULL DEFAULT (CURRENT_TIMESTAMP))");
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
            rc = db_exec(db1, "CREATE TABLE system_setting (id_systemsettings INTEGER PRIMARY KEY NOT NULL ,door_lock_timeOut SMALLINT NOT NULL ,open_door_timeOut SMALLINT NOT NULL)");
            if (rc != SQLITE_OK) {
                sqlite3_close(db1);
                return;
            }
            Serial.println("Table system_setting created successfully");
        }
        Serial.println("The system_setting table exists.");
    }
}

