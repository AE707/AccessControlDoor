#ifndef DB_OPERATIONS_H
#define DB_OPERATIONS_H

#include <sqlite3.h>

int db_open(const char *filename, sqlite3 **db);
int db_exec(sqlite3 *db, const char *sql);
int queryResultCallback(void *data, int argc, char **argv, char **azColName);
int callback(void *data, int argc, char **argv, char **azColName);

#endif // DB_OPERATIONS_H