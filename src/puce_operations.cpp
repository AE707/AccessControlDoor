#include "puce_operations.h"
#include "db_operations.h"
#include <Arduino.h>

void handlePuceStatus(sqlite3 *db1, int num_puce, char *num_state_p) {
    // Implement the logic to handle puce (chip) status
    /*--------------------------------------------------------------------PUCE--------------------------------------------------------------*/
    int rc;
    int tableExists;
    char* zErrMsg;
    char sql_check_puce[100];

rc = sqlite3_exec(db1, "SELECT count(*) FROM sqlite_master WHERE type='table' AND name='puce';", queryResultCallback, &tableExists, &zErrMsg);
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
        Serial.println("La table puce n'existe pas encore.");
        int rc = db_exec(db1, "CREATE TABLE puce (id_puce INTEGER PRIMARY KEY NOT NULL, statut TEXT NOT NULL, Alias TEXT NOT NULL, Date_expiration DATE NOT NULL, Id_utilisateur INTEGER NOT NULL, date_added DATE DEFAULT CURRENT_DATE)");
        if (rc != SQLITE_OK) {
            // Error in table creation
            sqlite3_close(db1);
            return;
        }
        Serial.println("Table created successfully");
    }
    Serial.println("La table puce existe.");
    rc = db_exec(db1, "INSERT INTO puce (id_puce, statut, Alias, Date_expiration, Id_utilisateur) VALUES (1, 'V', 'Rania_KZ', '2024-04-18', 12345);");
    if (rc != SQLITE_OK) {
        sqlite3_close(db1);
        return;
    }
}

// 2- Vérifier la date d'expiration
Serial.printf(sql_check_puce, "SELECT COUNT(*) FROM puce WHERE id_puce=%d and Date_expiration > CURRENT_DATE ;", num_puce);
rc = db_exec(db1, sql_check_puce);
if (rc != SQLITE_OK) {
    sqlite3_close(db1);
    return;
}

// Récupérer le résultat de la requête
int puce_valid = 0;
rc = sqlite3_exec(db1, sql_check_puce, queryResultCallback, &puce_valid, &zErrMsg);
if (rc != SQLITE_OK) {
    Serial.printf("Erreur lors de l'exécution de la requête SQL: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
    sqlite3_close(db1);
    return;
} else {
    // la date d'expiration est expirée
    if (!puce_valid) {
        Serial.println("La date d'expiration est expirée.");
        // ajouter num remarque de date expiree a num_state et puis ajouter num_state a la table evenement ...
        // date expire = 7
        num_state_p += '0111';
    } else {
        // la date d'expiration valide
        // 3- Vérifier si la puce vip ou non
        sprintf(sql_check_puce, "SELECT COUNT(*) FROM puce WHERE id_puce=%d and statut = 'V' ;", num_puce);
        rc = db_exec(db1, sql_check_puce);
        if (rc != SQLITE_OK) {
            sqlite3_close(db1);
            return;
        }

        // Récupérer le résultat de la requête
        rc = sqlite3_exec(db1, sql_check_puce, queryResultCallback, &puce_valid, &zErrMsg);
        if (rc != SQLITE_OK) {
            Serial.printf("Erreur lors de l'exécution de la requête SQL: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            sqlite3_close(db1);
            return;
        }

        // la puce est VIP
        if (puce_valid) {
            Serial.println("Puce VIP");
            // ajouter num remarque à num_state et puis ajouter num_state a la table evenement
            // normal acces (VIP) = 8
            num_state_p += '1000';
        } else {
            // la puce n'est pas VIP
            // 4- Vérifier si la puce Blacklist ou non
            sprintf(sql_check_puce, "SELECT COUNT(*) FROM puce WHERE id_puce=%d and statut = 'B' ;", num_puce);
            rc = db_exec(db1, sql_check_puce);
            if (rc != SQLITE_OK) {
                sqlite3_close(db1);
                return;
            }

            // Récupérer le résultat de la requête
            rc = sqlite3_exec(db1, sql_check_puce, queryResultCallback, &puce_valid, &zErrMsg);
            if (rc != SQLITE_OK) {
                Serial.printf("Erreur lors de l'exécution de la requête SQL: %s\n", zErrMsg);
                sqlite3_free(zErrMsg);
                sqlite3_close(db1);
                return;
            }

            // la puce est Blacklist
            if (puce_valid) {
                Serial.println("Puce Blacklist");
                // ajouter num_state à la table evenement
                // blacklist chip = 2
                num_state_p += '0010';
            } else {
                // la puce n'est pas blacklist
                // 5- Vérifier si la puce Desactiver ou non
                sprintf(sql_check_puce, "SELECT COUNT(*) FROM puce WHERE id_puce=%d and statut = 'D' ;", num_puce);
                rc = db_exec(db1, sql_check_puce);
                if (rc != SQLITE_OK) {
                    sqlite3_close(db1);
                    return;
                }

                // Récupérer le résultat de la requête
                rc = sqlite3_exec(db1, sql_check_puce, queryResultCallback, &puce_valid, &zErrMsg);
                if (rc != SQLITE_OK) {
                    Serial.printf("Erreur lors de l'exécution de la requête SQL: %s\n", zErrMsg);
                    sqlite3_free(zErrMsg);
                    sqlite3_close(db1);
                    return;
                }

                // la puce est Desactiver
                if (puce_valid) {
                    Serial.println("Puce desactiver");
                    // ajouter num_state à la table evenement
                    // puce desactiver = 3
                    num_state_p += '0011';
                } else {
                    // la puce n'est pas desactiver
                    // la puce est activer
                    // 6- Vérifier time zone
                    // - jointure de table puce et table time zone
                    // - verification de id puce et temps autoriser ...
                    // - si n'est pas autoriser , ajouter 4 '0100' à num state (Unauthorized Time zone )
                    // - si autoriser , ajouter 8 '1000' à num state (acces normal)
                }
            }
        }
    }
}
}