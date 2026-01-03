#ifndef DATABASE_H
#define DATABASE_H

#include <Arduino.h>
#include <sqlite3.h>

// Callback function for SQLite
static int callback(void *data, int argc, char **argv, char **azColName);

// Functions to handle database operations
int db_open(const char *filename, sqlite3 **db);
int db_exec(sqlite3 *db, const char *sql);
int queryResultCallback(void *data, int argc, char **argv, char **azColName);

// Function to check if a table exists
extern int tableExists;

#endif // DATABASE_H
