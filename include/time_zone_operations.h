#ifndef TIME_ZONE_OPERATIONS_H
#define TIME_ZONE_OPERATIONS_H

#include <sqlite3.h>

void verifyTimeZone(sqlite3 *db, int num_puce, char *num_state_p);

#endif // TIME_ZONE_OPERATIONS_H