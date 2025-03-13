#include "pin_setup.h"
#include "menu.h"
#include "setting.h"
#include "io.h"
#include "data.h"
#include "motor.h"
#include "sensor.h"
#include "wifi_setup.h"
#include "mqtt.h"


#define BAUD 115200

const char* deviceName = "AGROVOLTAIC";
const char* deviceModel = "ESP32-DEVKIT-V1";

unsigned long ppreviousMillis = 0;
const long interval = 1000;
int t;



// Task handles untuk menugaskan fungsi ke core tertentu
TaskHandle_t TaskCore0;
TaskHandle_t TaskCore1;

// Fungsi yang dijalankan di core1 (Baca input, sensor, dan tulis output)
void taskCore1(void *pvParameters) {
  while (true) {
    readDHT11();
    mqtt_loop();
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void setup() {
  Serial.begin(BAUD);
  pinSetup();
  menu_setup();
  inaSetup();
  setupDHT();
  mqtt_setup();
  wifi_setup();
  
  // Menjalankan task pada core1
  xTaskCreatePinnedToCore(
    taskCore1,   // Nama fungsi untuk core1
    "TaskCore1", // Nama task
    10000,       // Ukuran stack
    NULL,        // Parameter untuk task (NULL jika tidak ada)
    1,           // Prioritas task
    &TaskCore1,  // Task handle untuk core1
    1            // Core yang digunakan (core1)
  );
}

void loop() {
unsigned long currentMillis = millis(); // Mendapatkan waktu saat ini
 if (currentMillis - ppreviousMillis >= interval) {
   ppreviousMillis = currentMillis; // Simpan waktu saat ini
   t++;
 }
  menu_loop();
  autoManual();
  readIna219();
  writeOutput();
}

