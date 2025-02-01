#ifndef RECEIVEDATA_H
#define RECEIVEDATA_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include "savedata.h"

// Variabel global untuk menyimpan data dari MQTT
struct TimeData {
  int h, m, s;
};
extern void saveToEEPROMRd(int offTimeSeconds, int onTimeSeconds, TimeData sstartTime, TimeData sstopTime, bool s1, bool s2, bool s3, bool s4, String pSource);

TimeData offTime, onTime, sstartTime, sstopTime;
String powerSource;
bool s1, s2, s3, s4;
int offTimeSeconds, onTimeSeconds;


// Fungsi untuk memproses pesan MQTT berdasarkan topik
void processMQTTMessage(String topic, StaticJsonDocument<512>& doc) {
  if (topic == "ISOESP/noderedSetting") {
    
    // Parsing waktu "off"
    offTime.h = doc["off"]["h"];
    offTime.m = doc["off"]["m"];
    offTime.s = doc["off"]["s"];
    offTimeSeconds = (offTime.h * 3600) + (offTime.m * 60) + offTime.s; // Konversi ke detik

    // Parsing waktu "on"
    onTime.h = doc["on"]["h"];
    onTime.m = doc["on"]["m"];
    onTime.s = doc["on"]["s"];
    onTimeSeconds = (onTime.h * 3600) + (onTime.m * 60) + onTime.s; // Konversi ke detik


    // Parsing waktu "startTime"
    sstartTime.h = doc["startTime"]["h"];
    sstartTime.m = doc["startTime"]["m"];
    sstartTime.s = doc["startTime"]["s"];
    
    // Parsing waktu "stopTime"
    sstopTime.h = doc["stopTime"]["h"];
    sstopTime.m = doc["stopTime"]["m"];
    sstopTime.s = doc["stopTime"]["s"];

    // Parsing sumber daya "power"
    powerSource = doc["power"]["powerSource"].as<String>();

    // Parsing status boolean s1 - s4
    s1 = doc["s1"];
    s2 = doc["s2"];
    s3 = doc["s3"];
    s4 = doc["s4"];

    // Simpan data ke EEPROM
    saveToEEPROMRd(offTimeSeconds, onTimeSeconds, sstartTime, sstopTime, s1, s2, s3, s4, powerSource);

    // Menampilkan hasil parsing ke Serial Monitor
    // Menampilkan hasil parsing ke Serial Monitor
    Serial.println("=== Data Diterima dari MQTT ===");
    Serial.printf("Off Time: %02d:%02d:%02d (%d detik)\n", offTime.h, offTime.m, offTime.s, offTimeSeconds);
    Serial.printf("On Time: %02d:%02d:%02d (%d detik)\n", onTime.h, onTime.m, onTime.s, onTimeSeconds);
    Serial.printf("Start Time: %02d:%02d:%02d\n", sstartTime.h, sstartTime.m, sstartTime.s);
    Serial.printf("Stop Time: %02d:%02d:%02d\n", sstopTime.h, sstopTime.m, sstopTime.s);
    Serial.printf("Power Source: %s\n", powerSource.c_str());
    Serial.printf("S1: %s, S2: %s, S3: %s, S4: %s\n",
                  s1 ? "ON" : "OFF",
                  s2 ? "ON" : "OFF",
                  s3 ? "ON" : "OFF",
                  s4 ? "ON" : "OFF");
  }
  delay(1000);
}

#endif
