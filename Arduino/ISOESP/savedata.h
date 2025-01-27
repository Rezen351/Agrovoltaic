#ifndef SAVEDATA_H
#define SAVEDATA_H
#include <EEPROM.h>

// Ukuran EEPROM (disesuaikan dengan kebutuhan)
#define EEPROM_SIZE 512

// Alamat awal EEPROM untuk menyimpan data
#define INTERVAL_OFF 1
#define INTERVAL_ON 2
#define ISON 3

int data1, data2;
bool data3;
// Fungsi untuk menyimpan data ke EEPROM
void saveToEEPROM(int interval1, int interval2, bool isOn) {
  EEPROM.put(INTERVAL_OFF, interval1);  // Simpan intervalOff
  EEPROM.commit(); // Simpan perubahan ke EEPROM
  EEPROM.put(INTERVAL_ON, interval2);  // Simpan intervalOff
  EEPROM.commit(); // Simpan perubahan ke EEPROM
  EEPROM.put(ISON, isOn);  // Simpan intervalOff
  EEPROM.commit(); // Simpan perubahan ke EEPROM
  Serial.println("Data berhasil disimpan ke EEPROM");
}

// Fungsi untuk membaca data dari EEPROM
void loadFromEEPROM() {
  data1 = EEPROM.read(INTERVAL_OFF);
  data2 = EEPROM.read(INTERVAL_ON);
  data3 = EEPROM.read(ISON);
  Serial.println("Data terbaca dari EEPROM");
  Serial.println(data1);
  Serial.println(data2);
  Serial.println(data3);
}

void eepromSetup(){
  EEPROM.begin(EEPROM_SIZE);
  loadFromEEPROM();
}
#endif