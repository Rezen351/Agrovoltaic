#ifndef SETTING_H
#define SETTING_H
#include <TimeLib.h> // Library untuk menangani waktu
#include "savedata.h"

extern int data1, data2;
extern bool data3;

// Variabel global
int setIntervalOff = 10; // Interval Off dalam detik (dapat disesuaikan)
int setIntervalOn = 10;  // Interval On dalam detik (dapat disesuaikan)
int intervalOff;
int intervalOn;


String startTime = "00:00";
String stopTime = "23:59";

bool isOn = false; // Status apakah interval sedang dalam kondisi "On" atau "Off"


// Fungsi untuk mengecek waktu dalam rentang startTime dan stopTime
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

// Fungsi untuk menghitung interval
void calculateInterval(String currentTime) {
  isOn = data3;
  // Cek apakah waktu sekarang berada dalam rentang startTime dan stopTime
  if (isInTimeRange(currentTime, startTime, stopTime)) {
    if (isOn == true) { // Jika dalam kondisi On
    intervalOn = data2;
    intervalOff = setIntervalOff;
      intervalOn--;
      if (intervalOn <= 0) { // Jika interval On habis, beralih ke Off
        isOn = false;
        intervalOn = setIntervalOn; // Reset interval On
        Serial.println("Switched to Off interval");
      }
    } else { // Jika dalam kondisi Off
      intervalOff = data1;
      intervalOn = setIntervalOn;
      intervalOff--;
      if (intervalOff <= 0) { // Jika interval Off habis, beralih ke On
        isOn = true;
        intervalOff = setIntervalOff;
        Serial.println("Switched to On interval");
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
}

#endif
