#ifndef DB_OPERATIONS_H
#define DB_OPERATIONS_H

#include <sqlite3.h>
#include <PubSubClient.h>
#include <config_ext.h>

int db_open(const char *filename, sqlite3 **db);
int db_exec(sqlite3 *db, const char *sql);
int queryResultCallback(void *data, int argc, char **argv, char **azColName);
int callback(void *data, int argc, char **argv, char **azColName);

// Function to insert puce data from MQTT into the database
void insertPuceDataFromMQTT(sqlite3 *db, const char* topic, byte* payload, unsigned int length);

// Function to insert puce data into the database
void insertPuceData(sqlite3 *db, const char* query);

// Function to fetch data from the puce table
void fetchPuceData(sqlite3 *db, const char* query, PubSubClient& client);

// Callback function to process puce table data
int puceDataCallback(void *data, int argc, char **argv, char **azColName);

// Function to fetch data from the time_zone table
void fetchTimeZoneData(sqlite3 *db, const char* query, PubSubClient& client);

// Callback function to process time_zone table data
int timeZoneDataCallback(void *data, int argc, char **argv, char **azColName);

// Function to insert system setting data into the database
void insertSystemSettingData(sqlite3 *db, const char* query);

// Function to insert event data into the database
void insertEventData(sqlite3 *db, const char* query);

// Function to insert state data into the database
void insertStateData(sqlite3 *db, const char* query);

#endif // DB_OPERATIONS_H