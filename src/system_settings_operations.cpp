#include "system_settings_operations.h"
#include "db_operations.h"
#include <Arduino.h>

void loadSystemSettings(sqlite3 *db1) {
    // Implement the logic to load system settings
    /*------------------------------------------------------------SYSTEM_SETTINGS--------------------------------------------------------------*/
    int rc;
    int tableExists;
    char* zErrMsg;

rc = sqlite3_exec(db1, "SELECT count(*) FROM sqlite_master WHERE type='table' AND name='system_settings';", queryResultCallback, &tableExists, &zErrMsg);
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
        Serial.println("La table system_settings n'existe pas encore.");
        rc = db_exec(db1, "CREATE TABLE system_settings (id_systemsettings INTEGER PRIMARY KEY NOT NULL ,door_lock_timeOut SMALLINT NOT NULL ,open_door_timeOut SMALLINT NOT NULL );");
        if (rc != SQLITE_OK) {
            // prob de creation
            sqlite3_close(db1);
            return;
        }
        Serial.println("Creation done successfully");
    }
    Serial.println("La table system_settings existe.");
    // Load system settings logic can be added here
}
}