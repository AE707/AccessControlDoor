#include "puce_operations.h"
#include "db_operations.h"
#include <Arduino.h>
#include <PubSubClient.h>

char *zErrMsg = nullptr;


void checkPuceVIPStatus(sqlite3 *db, int num_puce, char *num_state_p) {
    char sql_query[100];
    sprintf(sql_query, "SELECT COUNT(*) FROM puce WHERE id_puce=%d and statut = 'V';", num_puce);
    int rc = db_exec(db, sql_query);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return;
    }

    int puce_valid = 0;
    rc = sqlite3_exec(db, sql_query, queryResultCallback, &puce_valid, &zErrMsg);
    if (rc != SQLITE_OK) {
        Serial.printf("Erreur lors de l'exécution de la requête SQL: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return;
    }

    if (puce_valid) {
        Serial.println("Puce VIP");
        strcat(num_state_p, "1000"); // Ensure num_state_p has enough space
    }
}

void handlePuceStatus(sqlite3 *db1, int num_puce, char *num_state_p, PubSubClient client) {
    checkPuceVIPStatus(db1, num_puce, num_state_p);

    // Fetch puce data from the database
    fetchPuceData(db1, "SELECT * FROM puce WHERE id_puce = ?", client);

    // Check expiration date
    int puce_valid = 0;
    char sql_check_puce[100];
    sprintf(sql_check_puce, "SELECT COUNT(*) FROM puce WHERE id_puce=%d and Date_expiration > CURRENT_DATE ;", num_puce);
    int rc = sqlite3_exec(db1, sql_check_puce, queryResultCallback, &puce_valid, &zErrMsg);
    if (!puce_valid) {
        Serial.println("La date d'expiration est expirée.");
        num_state_p += '0111';
        // Insert event data
        char event_query[200];
        sprintf(event_query, "INSERT INTO event (id_event , id_puce , state , date_heure_access) VALUES (%d, %d, %d, CURRENT_TIMESTAMP);", num_puce, 7, num_state_p);
        insertEventData(db1, event_query);
    } else {
        // Check VIP status
        sprintf(sql_check_puce, "SELECT COUNT(*) FROM puce WHERE id_puce=%d and statut = 'V' ;", num_puce);
        rc = sqlite3_exec(db1, sql_check_puce, queryResultCallback, &puce_valid, &zErrMsg);
        if (puce_valid) {
            Serial.println("Puce VIP");
            num_state_p += '1000';
        } else {
            // Check Blacklist status
            sprintf(sql_check_puce, "SELECT COUNT(*) FROM puce WHERE id_puce=%d and statut = 'B' ;", num_puce);
            rc = sqlite3_exec(db1, sql_check_puce, queryResultCallback, &puce_valid, &zErrMsg);
            if (puce_valid) {
                Serial.println("Puce Blacklist");
                num_state_p += '0010';
                // Insert event data
                char event_query[200];
                sprintf(event_query, "INSERT INTO event (id_event , id_puce , state , date_heure_access) VALUES (%d, %d, %d, CURRENT_TIMESTAMP);", num_puce, 2, num_state_p);
                insertEventData(db1, event_query);
            } else {
                // Check Desactiver status
                sprintf(sql_check_puce, "SELECT COUNT(*) FROM puce WHERE id_puce=%d and statut = 'D' ;", num_puce);
                rc = sqlite3_exec(db1, sql_check_puce, queryResultCallback, &puce_valid, &zErrMsg);
                if (puce_valid) {
                    Serial.println("Puce desactiver");
                    num_state_p += '0011';
                    // Insert event data
                    char event_query[200];
                    sprintf(event_query, "INSERT INTO event (id_event , id_puce , state , date_heure_access) VALUES (%d, %d, %d, CURRENT_TIMESTAMP);", num_puce, 3, num_state_p);
                    insertEventData(db1, event_query);
                } else {
                    // Fetch time_zone data from the database
                    fetchTimeZoneData(db1, "SELECT * FROM time_zone WHERE id = ?", client);
                    // Check time zone authorization
                    // ...
                }
            }
        }
    }

    // Insert state data
    //char state_query[200];
    //sprintf(state_query, "INSERT INTO state (state_name, state_code) VALUES ('state_name', '%s');", num_state_p);
    //insertStateData(db1, state_query);
}