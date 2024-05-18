#include "time_zone_operations.h"
#include "db_operations.h"
#include <Arduino.h>

void verifyTimeZone(sqlite3 *db1, int num_puce, char *num_state_p) {
    // Implement the logic to verify time zone
    /*---------------------------------------------------------------TIME_ZONE--------------------------------------------------------------*/
    int rc;
    int tableExists;
    char* zErrMsg;

rc = sqlite3_exec(db1, "SELECT count(*) FROM sqlite_master WHERE type='table' AND name='time_zone';", queryResultCallback, &tableExists, &zErrMsg);
if (rc != SQLITE_OK) {
    // problème
    Serial.printf("Erreur lors de l'exécution de la requête SQL: %s\n", zErrMsg);
    // En cas d'erreur, ferme la base de données et arrête l'exécution
    sqlite3_free(zErrMsg);
    sqlite3_close(db1);
    return;
} else {
    // traitement
    Serial.printf("Table existe (1 -> oui /0 -> non): %i\n", tableExists);
    if (!tableExists) {
        Serial.println("La table time_zone n'existe pas encore.");
        rc = db_exec(db1, "CREATE TABLE time_zone (id_timezone INTEGER PRIMARY KEY NOT NULL, day_of_week TINYINT NOT NULL, entry_time TIME NOT NULL, exit_time TIME NOT NULL, id_puce INTEGER NOT NULL, FOREIGN KEY (id_puce) REFERENCES puce(id_puce));");
        if (rc != SQLITE_OK) {
            // prob de creation
            sqlite3_close(db1);
            return;
        }
        Serial.println("Creation done successfully");
    }
    Serial.println("La table time_zone existe.");
    rc = db_exec(db1, "INSERT INTO time_zone VALUES (11,2,'10:00:00','12:00:00',1);");
    if (rc != SQLITE_OK) {
        sqlite3_close(db1);
        return;
    }
    rc = db_exec(db1, "SELECT * FROM time_zone");
    if (rc != SQLITE_OK) {
        sqlite3_close(db1);
        return;
    }
}
}