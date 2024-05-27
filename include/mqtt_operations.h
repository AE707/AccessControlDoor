#ifndef MQTT_OPERATIONS_H
#define MQTT_OPERATIONS_H

#include <PubSubClient.h>

void setup_mqtt(PubSubClient& client, const char* server, int port);
void mqtt_publish(PubSubClient& client, const char* topic, const char* message);
void mqtt_subscribe(PubSubClient& client, const char* topic);
void callback(char* topic, byte* payload, unsigned int length);

#endif