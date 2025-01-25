#ifndef WIFI_SETUP_H
#define WIFI_SETUP_H

#include <WiFi.h>

// WiFi credentials
const char* ssid = "eduroam";
#define EAP_IDENTITY "13322006@mahasiswa.itb.ac.id"
#define EAP_USERNAME "13322006@mahasiswa.itb.ac.id"
#define EAP_PASSWORD "Kyarajihan_152003"

void wifi_setup() {
  delay(10);
  Serial.println();
  Serial.print(F("Connecting to network: "));
  Serial.println(ssid);
  WiFi.disconnect(true);
  WiFi.mode(WIFI_STA);    //init wifi mode
  WiFi.begin(ssid, WPA2_AUTH_PEAP, EAP_IDENTITY, EAP_USERNAME, EAP_PASSWORD);

    WiFi.begin(ssid);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(F("."));
    }

    Serial.println(F("\nWiFi is connected!"));
    Serial.print(F("IP address: "));
    Serial.println(WiFi.localIP());
}

#endif
