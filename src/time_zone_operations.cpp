#include "time_zone_operations.h"
#include "db_operations.h"
#include <Arduino.h>

void verifyTimeZone(sqlite3 *db1, int num_puce, char *num_state_p) {
    // Fetch time_zone data from the database
    fetchTimeZoneData(db1, "SELECT * FROM time_zone WHERE id_puce = ?", num_puce);

    // Get the current time
    unsigned long currentTime = millis() / 1000; // Assuming millis() returns milliseconds since startup
    unsigned long currentTimeOfDay = currentTime % 86400; // Seconds since midnight

    // Iterate through the fetched time_zone data
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int dayOfWeek = sqlite3_column_int(stmt, 1);
        unsigned long entryTime = parseTimeString(sqlite3_column_text(stmt, 2)); // Parse entry_time string to seconds since midnight
        unsigned long exitTime = parseTimeString(sqlite3_column_text(stmt, 3)); // Parse exit_time string to seconds since midnight

        // Check if the current day matches the day_of_week in the time_zone table
        if (dayOfWeek == getCurrentDayOfWeek()) {
            // Check if the current time is within the authorized time range
            if (currentTimeOfDay >= entryTime && currentTimeOfDay <= exitTime) {
                // Access allowed
                num_state_p += '1000'; // Set the access allowed flag in num_state_p
                return;
            }
        }
    }

    // Access denied
    num_state_p += '0100'; // Set the unauthorized time zone flag in num_state_p
}

// Helper function to parse a time string in the format "HH:MM:SS" to seconds since midnight
unsigned long parseTimeString(const char* timeString) {
    int hours, minutes, seconds;
    sscanf(timeString, "%d:%d:%d", &hours, &minutes, &seconds);
    return hours * 3600 + minutes * 60 + seconds;
}

// Helper function to get the current day of the week (1-7, where 1 is Monday and 7 is Sunday)
int getCurrentDayOfWeek() {
    // Implement a function to get the current day of the week based on your system's date/time
    // This example assumes a simple implementation using millis()
    return ((millis() / (24 * 3600 * 1000)) % 7) + 1;
}