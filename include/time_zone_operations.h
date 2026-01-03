#ifndef TIME_ZONE_OPERATIONS_H
#define TIME_ZONE_OPERATIONS_H

#include <sqlite3.h>
#include <PubSubClient.h>

// Function to fetch data from the time_zone table in the database
void fetchTimeZoneData(sqlite3 *db, const char* query, PubSubClient& client);

// Callback function to process query results for time zone data
int queryResultCallback(void *data, int argc, char **argv, char **azColName);

// Function to insert time zone data into the time_zone table in the database
void insertTimeZoneData(sqlite3 *db, const char* query);

// Function to update time zone data in the time_zone table in the database
void updateTimeZoneData(sqlite3 *db, const char* query);

// Function to delete time zone data from the time_zone table in the database
void deleteTimeZoneData(sqlite3 *db, const char* query);
// Helper function to parse a time string in the format "HH:MM:SS" to seconds since midnight


// Helper function to get the current day of the week (1-7, where 1 is Monday and 7 is Sunday)
int getCurrentDayOfWeek() {
    // Implement a function to get the current day of the week based on your system's date/time
    // This example assumes a simple implementation using millis()
    return ((millis() / (24 * 3600 * 1000)) % 7) + 1;
}

#endif // TIME_ZONE_OPERATIONS_H