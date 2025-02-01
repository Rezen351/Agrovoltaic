#ifndef SAVEDATA_H
#define SAVEDATA_H
#include <EEPROM.h>
#include "receivedata.h"
// Ukuran EEPROM (disesuaikan dengan kebutuhan)
#define EEPROM_SIZE 512

// Alamat awal EEPROM untuk menyimpan data
#define INTERVAL_OFF 0
#define INTERVAL_ON 4
#define ISON 8


int d1, d2, d4, d5;
bool d3, d6, d7, d8, d9;
extern TimeData estartTime, estopTime;
char epowerSource[20]; // Buffer untuk menyimpan powerSource

// Fungsi untuk menyimpan data ke EEPROM
void saveToEEPROMRd(int offTimeSeconds, int onTimeSeconds, TimeData sstartTime, TimeData sstopTime, bool s1, bool s2, bool s3, bool s4, String pSource) {
  EEPROM.put(10, offTimeSeconds);
  EEPROM.put(14, onTimeSeconds);
  EEPROM.put(18, sstartTime);
  EEPROM.put(30, sstopTime);
  EEPROM.put(42, s1);
  EEPROM.put(43, s2);
  EEPROM.put(44, s3);
  EEPROM.put(45, s4);

  // Simpan String powerSource sebagai char array
  pSource.toCharArray(epowerSource, sizeof(epowerSource));
  EEPROM.put(46, epowerSource);

  EEPROM.commit();  // Simpan data ke EEPROM
  Serial.println("Data berhasil disimpan ke EEPROM");
}

void saveToEEPROM(int interval1, int interval2, bool isOn) {
  EEPROM.put(INTERVAL_OFF, interval1);
  EEPROM.put(INTERVAL_ON, interval2);
  EEPROM.put(ISON, isOn);
  EEPROM.commit(); // Simpan perubahan ke EEPROM
  Serial.println("Data berhasil disimpan ke EEPROM");
}

// Fungsi untuk membaca data dari EEPROM
void loadFromEEPROM() {
  EEPROM.get(INTERVAL_OFF, d1);
  EEPROM.get(INTERVAL_ON, d2);
  EEPROM.get(ISON, d3);
  EEPROM.get(10, d4);
  EEPROM.get(14, d5);
  // EEPROM.get(18, estartTime);
  // EEPROM.get(30, estopTime);
  EEPROM.get(42, d6);
  EEPROM.get(43, d7);
  EEPROM.get(44, d8);
  EEPROM.get(45, d9);
  EEPROM.get(46, epowerSource);

  Serial.println("=== Data terbaca dari EEPROM: ===");
  Serial.printf("Interval Off: %d sec\n", d1);
  Serial.printf("Interval On: %d sec\n", d2);
  Serial.printf("Off Time: %d sec\n", d4);
  Serial.printf("On Time: %d sec\n", d5);
  // Serial.printf("Start Time: %02d:%02d:%02d\n", estartTime.h, estartTime.m, estartTime.s);
  // Serial.printf("Stop Time: %02d:%02d:%02d\n", estopTime.h, estopTime.m, estopTime.s);
  Serial.printf("Power Source: %s\n", epowerSource);
  Serial.printf("S1: %s, S2: %s, S3: %s, S4: %s\n", d6 ? "ON" : "OFF", d7 ? "ON" : "OFF", d8 ? "ON" : "OFF", d9 ? "ON" : "OFF");
  delay(1000);
}

void eepromSetup() {
  EEPROM.begin(EEPROM_SIZE);
  loadFromEEPROM();
}

#endif
