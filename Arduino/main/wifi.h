
#ifndef WIFI_SETUP_H
#define WIFI_SETUP_H

#include <WiFi.h>

// WiFi credentials
const char* ssid = "eduroam";
#define EAP_IDENTITY "13322006@mahasiswa.itb.ac.id"
#define EAP_USERNAME "13322006@mahasiswa.itb.ac.id"
#define EAP_PASSWORD "Kyarajihan_152003"
TaskHandle_t wifiTaskHandle;
void wifiTask(void *pvParameters) {
  while (true) {
    // Cek status Wi-Fi
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println(F("WiFi not connected. Attempting to connect..."));

      // Mulai koneksi Wi-Fi
      WiFi.disconnect(true);
      WiFi.begin(ssid, WPA2_AUTH_PEAP, EAP_IDENTITY, EAP_USERNAME, EAP_PASSWORD);

      // Tunggu hingga koneksi berhasil atau timeout (maksimal 10 detik)
      unsigned long startTime = millis();
      while (WiFi.status() != WL_CONNECTED && millis() - startTime < 10000) {
        delay(500);
        Serial.print(F("."));
      }

      if (WiFi.status() == WL_CONNECTED) {
        Serial.println(F("\nWiFi connected successfully!"));
        Serial.print(F("IP address: "));
        Serial.println(WiFi.localIP());
      } else {
        Serial.println(F("\nWiFi connection failed. Will retry..."));
      }
    } else {
      // Jika sudah terhubung, tunggu beberapa saat sebelum memeriksa kembali
      delay(5000); // Cek ulang setiap 5 detik
    }
  }
}

void wifi_setup() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect(true);
  Serial.println(F("WiFi setup initialized."));

  // Jalankan task Wi-Fi pada core0
  xTaskCreatePinnedToCore(
    wifiTask,       // Fungsi task
    "WiFiTask",     // Nama task
    4096,           // Ukuran stack
    NULL,           // Parameter untuk task
    1,              // Prioritas task
    &wifiTaskHandle,// Task handle
    0               // Core yang digunakan (core0)
  );
}

#endif
