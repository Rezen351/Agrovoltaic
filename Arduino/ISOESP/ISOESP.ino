#include "pin_setup.h"
#include "menu.h"
#include "setting.h"
#include "input.h"
#include "output.h"
#include "sensor.h"
#include "wifi_setup.h"
#include "mqtt.h"
#include "data.h"
#include "savedata.h"
#include "receivedata.h"
#define BAUD 115200

const char* deviceName = "AGROVOLTAIC";
const char* deviceModel = "ESP32-DEVKIT-V1";

// Task handles untuk menugaskan fungsi ke core tertentu
TaskHandle_t TaskCore0;
TaskHandle_t TaskCore1;


// Fungsi yang dijalankan di core0 (Wi-Fi, MQTT, dan mengirim data)
void taskCore0(void *pvParameters) {
  while (true) {
    mqtt_setup();
    mqtt_loop();   // Proses MQTT
    send_all_data(); // Mengirim data
  }
}

// Fungsi yang dijalankan di core1 (Baca input, sensor, dan tulis output)
void taskCore1(void *pvParameters) {
  while (true) {
    loadFromEEPROM();
    readAnalog();   // Membaca nilai analog
    readDigital();  // Membaca nilai digital
    // printInput();
    writeOutput();  // Menulis output
    sensor_setup();
    sensor_loop();  // Memproses data sensor
    String currentTime = String(hour()) + ":" + String(minute());
    calculateInterval(currentTime);
    menu_loop();
  }
}

void setup() {
  Serial.begin(BAUD);
  pinSetup();
  wifi_setup();
  eepromSetup();
  menu_setup();
  // Menjalankan task pada core0
  xTaskCreatePinnedToCore(
    taskCore0,   // Nama fungsi untuk core0
    "TaskCore0", // Nama task
    10000,       // Ukuran stack
    NULL,        // Parameter untuk task (NULL jika tidak ada)
    1,           // Prioritas task
    &TaskCore0,  // Task handle untuk core0
    0            // Core yang digunakan (core0)
  );

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
}
