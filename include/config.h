// config.h
#ifndef CONFIG_H
#define CONFIG_H

// WiFi settings
const char* ssid = "Alaa's A34";
const char* password = "1234567890";

// MQTT settings
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;

// NTP settings
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 0;
const int daylightOffset_sec = 3600;

#endif