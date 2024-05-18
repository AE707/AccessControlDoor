#include "db_operations.h"
#include <Arduino.h>

const char *data = "Callback function called";

int callback(void *data, int argc, char **argv, char **azColName) {
    int i;
    Serial.printf("%s: ", (const char *)data);
    for (i = 0; i < argc; i++) {
        Serial.printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    Serial.printf("\n");
    return 0;
}

int db_open(const char *filename, sqlite3 **db) {
    int rc = sqlite3_open(filename, db);
    if (!rc) {
        Serial.printf("Opened database successfully\n");
    } else {
        Serial.printf("Can't open database: %s\n", sqlite3_errmsg(*db));
    }
    return !rc;
}

 *zErrMsg = 0;

int db_exec(sqlite3 *db, const char *sql) {
    Serial.println(sql);
    long start = micros();
    int rc = sqlite3_exec(db, sql, callback, (void *)data, &zErrMsg);
    if (rc != SQLITE_OK) {
        Serial.printf("SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        *zErrMsg = 0;
    } else {
        Serial.printf("Operation done successfully\n");
    }
    Serial.print(F("Time taken:"));
    Serial.println(micros() - start);
    return rc;
}

int queryResultCallback(void *data, int argc, char **argv, char **azColName) {
    int *tableExists = (int *)data;
    *tableExists = atoi(argv[0]);
    return 0;
}