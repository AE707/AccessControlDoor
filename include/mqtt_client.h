#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <WiFi.h>
#include <PubSubClient.h>

// WiFi credentials
extern const char* ssid;
extern const char* password;

// MQTT Broker details
extern const char* mqtt_broker;
extern const char* topic;
extern const char* mqtt_username;
extern const char* mqtt_password;
extern const int mqtt_port;

extern WiFiClient espClient;
extern PubSubClient client;

void setup_wifi();
void setup_mqtt();
void mqtt_callback(char* topic, byte* payload, unsigned int length);

#endif
