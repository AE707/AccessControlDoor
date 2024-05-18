#ifndef PUCE_OPERATIONS_H
#define PUCE_OPERATIONS_H

#include <sqlite3.h>

void handlePuceStatus(sqlite3 *db, int num_puce, char *num_state_p);

#endif // PUCE_OPERATIONS_H