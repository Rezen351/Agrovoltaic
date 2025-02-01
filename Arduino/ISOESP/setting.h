#ifndef SETTING_H
#define SETTING_H
#include <TimeLib.h> // Library untuk menangani waktu
#include "savedata.h"

extern int d1, d2, d4, d5;
extern bool d3;

// ✅ Variabel global
int setIntervalOff = 10; // Interval Off dalam detik (dapat disesuaikan)
int setIntervalOn = 10;  // Interval On dalam detik (dapat disesuaikan)
int intervalOff;
int intervalOn;

// ✅ Fungsi untuk memperbarui interval berdasarkan EEPROM
void updateIntervals() {
  if (setIntervalOff != d4) {
    setIntervalOff = d4;
  }
  if (setIntervalOn != d5) {
    setIntervalOn = d5;
  }
}


String startTime = "00:00";
String stopTime = "23:59";

bool isOn = false; // Status apakah interval sedang dalam kondisi "On" atau "Off"


// ✅ Fungsi untuk mengecek waktu dalam rentang startTime dan stopTime
bool isInTimeRange(String currentTime, String startTime, String stopTime) {
  int currentHour = currentTime.substring(0, 2).toInt();
  int currentMinute = currentTime.substring(3, 5).toInt();
  int startHour = startTime.substring(0, 2).toInt();
  int startMinute = startTime.substring(3, 5).toInt();
  int stopHour = stopTime.substring(0, 2).toInt();
  int stopMinute = stopTime.substring(3, 5).toInt();

  int currentTotalMinutes = currentHour * 60 + currentMinute;
  int startTotalMinutes = startHour * 60 + startMinute;
  int stopTotalMinutes = stopHour * 60 + stopMinute;

  return currentTotalMinutes >= startTotalMinutes && currentTotalMinutes <= stopTotalMinutes;
}

// ✅ Fungsi untuk menghitung interval
void calculateInterval(String currentTime) {
  updateIntervals();  // Pastikan interval diperbarui
  isOn = d3;
  // Cek apakah waktu sekarang berada dalam rentang startTime dan stopTime
  if (isInTimeRange(currentTime, startTime, stopTime)) {
    if (isOn == true) { // Jika dalam kondisi On
    intervalOn = d2;
    intervalOff = setIntervalOff;
      intervalOn--;
      if (intervalOn <= 0) { // Jika interval On habis, beralih ke Off
        isOn = false;
        intervalOn = setIntervalOn; // Reset interval On
      }
    } else { // Jika dalam kondisi Off
      intervalOff = d1;
      intervalOn = setIntervalOn;
      intervalOff--;
      if (intervalOff <= 0) { // Jika interval Off habis, beralih ke On
        isOn = true;
        intervalOff = setIntervalOff;
      }
    }
  } else {
    // Jika di luar rentang waktu, pastikan interval dalam kondisi Off
    Serial.println("Outside active time range");
    isOn = false;
    intervalOff = setIntervalOff;
    intervalOn = setIntervalOn;
  }
  int interval1 = intervalOff;
  int interval2 = intervalOn;
  saveToEEPROM(interval1, interval2, isOn);
  delay(1000);
}

#endif
