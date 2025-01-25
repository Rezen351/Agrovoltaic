#include <PubSubClient.h>

const char* mqtt_server = "broker.mqtt-dashboard.com";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  String topicStr = String(topic);
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Menghubungkan ke MQTT...");
    if (client.connect("ArduinoClient")) {
      Serial.println("Terhubung");
      client.subscribe("ISOESP1/data");
    } else {
      Serial.print("Gagal, rc=");
      Serial.print(client.state());
      Serial.println(" Coba lagi dalam 5 detik");
      delay(5000);
    }
  }
}

void mqtt_setup() {
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void mqtt_loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
