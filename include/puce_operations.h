#ifndef PUCE_OPERATIONS_H
#define PUCE_OPERATIONS_H

#include <sqlite3.h>
#include <PubSubClient.h>

// Function to check the VIP status of a RFID tag in the database
void checkPuceVIPStatus(sqlite3 *db, int num_puce, char *num_state_p);

// Function to handle the status of a RFID tag based on various conditions
void handlePuceStatus(sqlite3 *db1, int num_puce, char *num_state_p, PubSubClient client);

// Function to fetch data from the puce table in the database
void fetchPuceData(sqlite3 *db, const char* query, PubSubClient& client);

// Callback function to process query results for puce data
int queryResultCallback(void *data, int argc, char **argv, char **azColName);

// Function to fetch data from the time_zone table in the database
void fetchTimeZoneData(sqlite3 *db, const char* query, PubSubClient& client);

#endif // PUCE_OPERATIONS_H