#include <WiFi.h>
#include "sensor.h"
#include "wifi.h"
#include "mqtt.h"
#include "pinSetup.h"
#include "outputControl.h"
#include "send_data.h"

#define BAUD 9600

void setup() {
  Serial.begin(BAUD);
  pinSetup();
  wifi_setup();
  sensor_setup();
  mqtt_setup();
}

void loop() {
  readAnalog();
  readDigital();
  printInput();
  writeOutput();
  sensor_loop();
  mqtt_loop();
  send_all_data();
  delay(1000);  // Wait for 1 second before next loop
}
