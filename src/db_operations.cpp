#include "db_operations.h"
#include <Arduino.h>

// Function to insert puce data from MQTT into the database
void insertPuceDataFromMQTT(sqlite3 *db, const char* topic, byte* payload, unsigned int length) {
    if (strcmp(topic, "puce/data") == 0) {
        char puceData[length + 1];
        strncpy(puceData, (char*)payload, length);
        puceData[length] = '\0';
        
        // Parse the puce data and extract relevant fields
        char* id_puce = strtok(puceData, ";");
        char* statut = strtok(NULL, ";");
        char* alias = strtok(NULL, ";");
        char* date_expiration = strtok(NULL, ";");
        char* id_utilisateur = strtok(NULL, ";");
        
        // Prepare the SQL query to insert data into the puce table
        char sql_query[200];
        sprintf(sql_query, "INSERT INTO puce (id_puce, statut, Alias, Date_expiration, Id_utilisateur) VALUES (%s, '%s', '%s', '%s', %s);", id_puce, statut, alias, date_expiration, id_utilisateur);
        
        // Insert the puce data into the database
        insertPuceData(db, sql_query);
    }
}

// Function to insert puce data into the database
void insertPuceData(sqlite3 *db, const char* query) {
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, query, NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        Serial.printf("SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
}

// Function to fetch data from the puce table
void fetchPuceData(sqlite3 *db, const char* query, PubSubClient& client) {
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, query, puceDataCallback, &client, &zErrMsg);
    if (rc != SQLITE_OK) {
        Serial.printf("SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
}

// Callback function to process puce table data
int puceDataCallback(void *data, int argc, char **argv, char **azColName) {
    PubSubClient* client = (PubSubClient*)data;
    String puceData = "";
    for (int i = 0; i < argc; i++) {
        puceData += String(azColName[i]) + "=" + String(argv[i] ? argv[i] : "NULL") + ";";
    }
    mqtt_publish(*client, "puce/data", puceData.c_str());
    return 0;
}

// Function to fetch data from the time_zone table
void fetchTimeZoneData(sqlite3 *db, const char* query, PubSubClient& client) {
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, query, timeZoneDataCallback, &client, &zErrMsg);
    if (rc != SQLITE_OK) {
        Serial.printf("SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
}

// Callback function to process time_zone table data
int timeZoneDataCallback(void *data, int argc, char **argv, char **azColName) {
    PubSubClient* client = (PubSubClient*)data;
    String timeZoneData = "";
    for (int i = 0; i < argc; i++) {
        timeZoneData += String(azColName[i]) + "=" + String(argv[i] ? argv[i] : "NULL") + ";";
    }
    mqtt_publish(*client, "time_zone/data", timeZoneData.c_str());
    return 0;
}

// Function to insert system setting data into the database
void insertSystemSettingData(sqlite3 *db, const char* query) {
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, query, NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        Serial.printf("SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
}

// Function to insert event data into the database
void insertEventData(sqlite3 *db, const char* query) {
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, query, NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        Serial.printf("SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
}

// Function to insert state data into the database
void insertStateData(sqlite3 *db, const char* query) {
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, query, NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        Serial.printf("SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
}