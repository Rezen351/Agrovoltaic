#include "pin_setup.h"
#include "input.h"
#include "output.h"
#include "sensor.h"
#include "wifi_setup.h"
#include "mqtt.h"
#include "data.h"

#define BAUD 115200

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
  writeOutput();
  sensor_loop();
  mqtt_loop();
  send_all_data();
  delay(1000);
}
