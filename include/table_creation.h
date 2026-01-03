#ifndef TABLE_CREATION_H
#define TABLE_CREATION_H

#include <sqlite3.h>

void createPuceTable(sqlite3 *db1);
void createTimeZoneTable(sqlite3 *db1);
void createJourTable(sqlite3 *db1);
void createTimeSlotTable(sqlite3 *db1);
void createJourTimeSlotTable(sqlite3 *db1);
void createTimezoneJourTimeSlotTable(sqlite3 *db1);
void createEventTable(sqlite3 *db1);
void createSystemSettingTable(sqlite3 *db1);

#endif