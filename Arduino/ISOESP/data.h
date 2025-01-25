#ifndef DATA_H
#define DATA_H

#include <ArduinoJson.h>
extern float humi1,temp1,humi2,temp2,humi3,temp3;
extern int analogValueA1,analogValueA2,digitalStateS1,digitalStateS2,digitalStateR1,digitalStateR2,digitalStateRR1,digitalStateRR2;

void send_all_data() {
  // Membuat JSON dengan ArduinoJson
  StaticJsonDocument<256> doc;
  // Sensor Data
  JsonObject sensor1 = doc.createNestedObject("Sensor1");
  sensor1["Temperature"] = isnan(temp1) ? -404 : temp1;
  sensor1["Humidity"] = isnan(humi1) ? -404 : humi1;

  JsonObject sensor2 = doc.createNestedObject("Sensor2");
  sensor2["Temperature"] = isnan(temp2) ? -404 : temp2;
  sensor2["Humidity"] = isnan(humi2) ? -404 : humi2;

  JsonObject sensor3 = doc.createNestedObject("Sensor3");
  sensor3["Temperature"] = isnan(temp3) ? -404 : temp3;
  sensor3["Humidity"] = isnan(humi3) ? -404 : humi3;

  // Analog Input
  JsonObject analogInput = doc.createNestedObject("AI");
  analogInput["AI1"] = isnan(analogValueA1) ? -404 : analogValueA1;
  analogInput["AI2"] = isnan(analogValueA2) ? -404 : analogValueA2;

  // Digital Input
  JsonObject digitalInput = doc.createNestedObject("DI");
  digitalInput["DI1"] = isnan(digitalStateS1) ? -404 : digitalStateS1;
  digitalInput["DI2"] = isnan(digitalStateS1) ? -404 : digitalStateS1;

  // Digital Output
  JsonObject digitalOutput = doc.createNestedObject("DO");
  digitalOutput["R1"] = isnan(digitalStateR1) ? -404 : digitalStateR1;
  digitalOutput["R2"] = isnan(digitalStateR2) ? -404 : digitalStateR2;
  digitalOutput["RR1"] = isnan(digitalStateRR1) ? -404 : digitalStateRR1;
  digitalOutput["RR2"] = isnan(digitalStateRR2) ? -404 : digitalStateRR2;
  // Serialisasi JSON ke string
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer);
  
  if (!client.connected()) {
    reconnect();
  }
  client.publish("ISOESP1/data", jsonBuffer);  // Publikasi payload ke topik
  Serial.println("Data terkirim:");
  Serial.println(jsonBuffer);
}
#endif 