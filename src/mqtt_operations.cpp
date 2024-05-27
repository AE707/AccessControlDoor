#include "mqtt_operations.h"

// Callback function to handle incoming messages
void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}

// Setup MQTT connection
void setup_mqtt(PubSubClient& client, const char* server, int port) {
    client.setServer(server, port);
    client.setCallback(callback);
}

// Function to publish messages
void mqtt_publish(PubSubClient& client, const char* topic, const char* message) {
    if (client.connect("ESP32Client")) {
        client.publish(topic, message);
    }
}

// Function to subscribe to topics
void mqtt_subscribe(PubSubClient& client, const char* topic) {
    if (client.connect("ESP32Client")) {
        client.subscribe(topic);
    }
}