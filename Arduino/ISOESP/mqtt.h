#ifndef MQTT_H
#define MQTT_H
#include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "receivedata.h"

// MQTT Broker
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;

// Client untuk WIFI dan MQTT
WiFiClient Client;
PubSubClient client(Client);

// Fungsi callback untuk menangani pesan yang diterima dari MQTT
void callback(char* topic, byte* payload, unsigned int length) {
  // Konversi payload ke string
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  // Parsing JSON
  StaticJsonDocument<512> doc;
  DeserializationError error = deserializeJson(doc, message);

  if (error) {
    Serial.print("Parsing JSON gagal: ");
    Serial.println(error.f_str());
    return;
  }
  // Memproses JSON berdasarkan topik
  processMQTTMessage(topic, doc);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Menghubungkan ke MQTT...");
    if (client.connect("ArduinoClient")) {
      Serial.println("Terhubung");
      // Subscribe ke topik yang diperlukan
      client.subscribe("ISOESP/noderedSetting");
    } else {
      Serial.print("Gagal, rc=");
      Serial.print(client.state());
      Serial.println(" Coba lagi dalam 5 detik");
      delay(5000);
    }
  }
}


void mqtt_setup(){
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void mqtt_loop(){
  // Jika belum terhubung ke MQTT, coba sambungkan kembali
  if (!client.connected()) {
    reconnect();
  }
  client.loop();  // Mengatur loop MQTT
}
#endif 