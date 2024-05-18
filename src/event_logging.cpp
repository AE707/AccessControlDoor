#include "event_logging.h"
#include "db_operations.h"
#include <Arduino.h>

void logEvent(sqlite3 *db1, int num_puce, char *num_state) {
    // Implement the logic to log events
    /*----------------------------------------------------------------EVENEMENT-------------------------------------------------------------------*/
    int rc;
    int tableExists;
    char* zErrMsg;

rc = sqlite3_exec(db1, "SELECT count(*) FROM sqlite_master WHERE type='table' AND name='evenement';", queryResultCallback, &tableExists, &zErrMsg);
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
        Serial.println("La table evenement n'existe pas encore.");
        rc = db_exec(db1, "CREATE TABLE evenement (id_evenement INTEGER PRIMARY KEY NOT NULL ,date_heur_acces DATETIME DEFAULT CURRENT_TIMESTAMP,state TINYINT NOT NULL,FOREIGN KEY (id_puce) REFERENCES puce (id_puce));");
         // Additional code for table creation
        if (rc != SQLITE_OK) {
            // prob de creation
            sqlite3_close(db1);
            return;
        }
        Serial.println("Creation done successfully");
    }
    Serial.println("La table evenement existe.");
    /* --> */
    rc = db_exec(db1, "INSERT INTO evenement (state,id_puce) VALUES (12,1);");
    if (rc != SQLITE_OK) {
        sqlite3_close(db1);
        return;
    }
    rc = db_exec(db1, "SELECT * FROM evenement");
    if (rc != SQLITE_OK) {
        sqlite3_close(db1);
        return;
    }
}
}