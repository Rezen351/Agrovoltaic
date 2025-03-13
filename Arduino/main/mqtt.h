#ifndef MQTT_H
#define MQTT_H
// #include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

// MQTT Broker
const char* mqtt_server = "broker.emqx.io";
const int mqtt_port = 1883;

// Client untuk WIFI dan MQTT
WiFiClient Client;
PubSubClient client(Client);

// Fungsi callback untuk menangani pesan yang diterima dari MQTT
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Pesan diterima di topik: ");
  Serial.println(topic);

  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.print("Isi pesan: ");
  Serial.println(message);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Menghubungkan ke MQTT...");
    if (client.connect("ESP32")) {
      Serial.println("Terhubung");
      // Subscribe ke topik yang diperlukan
      client.subscribe("AGROVOLTAIC/sensors");            
    } else {
      Serial.print("Gagal, rc=");
      Serial.print(client.state());
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
