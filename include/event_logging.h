#ifndef EVENT_LOGGING_H
#define EVENT_LOGGING_H

#include <sqlite3.h>

void logEvent(sqlite3 *db, int num_puce, char *num_state);

#endif // EVENT_LOGGING_H