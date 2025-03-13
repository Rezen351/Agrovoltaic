#ifndef DATA_H
#define DATA_H

#include "menu.h"
#include "io.h"

// Data terdiri dari kondisi GPIO, Interval, Start and Stop Time
extern int analogValueA1, analogValueA2;
extern bool digitalStateS1, digitalStateS2, digitalStateR1, digitalStateR2, digitalStateRR1, digitalStateRR2;
extern int intervalminON, intervalsecON, intervalminOFF, intervalsecOFF;
extern int startHour, startMinute, stopHour, stopMinute;


// Fungsi untuk menyimpan data ke Preferences
void saveData() {
  prefs.begin("data", false); // false = Write mode
  
  // Menyimpan data analog
  prefs.putInt("pA1", analogValueA1);
  prefs.putInt("pA2", analogValueA2);

  // Menyimpan data digital (GPIO)
  prefs.putBool("pS1", digitalStateS1);
  prefs.putBool("pS2", digitalStateS2);
  prefs.putBool("pR1", digitalStateR1);
  prefs.putBool("pR2", digitalStateR2);
  prefs.putBool("pRR1", digitalStateRR1);
  prefs.putBool("pRR2", digitalStateRR2);

  // Menyimpan interval ON/OFF
  int intervalON = (intervalminON * 60) + intervalsecON;
  int intervalOFF = (intervalminOFF * 60) + intervalsecOFF;
  prefs.putInt("pintervalON", intervalON);
  prefs.putInt("pintervalOFF", intervalOFF);

  // Menggabungkan Start dan Stop Time ke string
  String startTime = String(startHour) + ":" + String(startMinute);
  String stopTime = String(stopHour) + ":" + String(stopMinute);
  prefs.putString("pstartTime", startTime);
  prefs.putString("pstopTime", stopTime);

  prefs.end(); // Tutup Preferences setelah menyimpan

  Serial.println("Data disimpan ke Preferences.");
}

// Fungsi untuk memuat data dari Preferences
void loadData() {
  prefs.begin("data", true); // true = Read mode

  // Memuat data analog
  analogValueA1 = prefs.getInt("pA1", 0);
  analogValueA2 = prefs.getInt("pA2", 0);

  // Memuat data digital (GPIO)
  digitalStateS1 = prefs.getBool("pS1", false);
  digitalStateS2 = prefs.getBool("pS2", false);
  digitalStateR1 = prefs.getBool("pR1", false);
  digitalStateR2 = prefs.getBool("pR2", false);
  digitalStateRR1 = prefs.getBool("pRR1", false);
  digitalStateRR2 = prefs.getBool("pRR2", false);

  // Memuat interval ON/OFF dalam detik dan mengonversinya kembali ke menit dan detik
  int intervalON = prefs.getInt("pintervalON", 600);
  int intervalOFF = prefs.getInt("pintervalOFF", 600);
  intervalminON = intervalON / 60;
  intervalsecON = intervalON % 60;
  intervalminOFF = intervalOFF / 60;
  intervalsecOFF = intervalOFF % 60;

  // Memuat Start dan Stop Time
  String startTime = prefs.getString("pstartTime", "6:0");
  String stopTime = prefs.getString("pstopTime", "18:0");
  sscanf(startTime.c_str(), "%d:%d", &startHour, &startMinute);
  sscanf(stopTime.c_str(), "%d:%d", &stopHour, &stopMinute);

  prefs.end(); // Tutup Preferences setelah memuat

  // Menampilkan data yang dimuat di Serial Monitor
  Serial.println("Data dimuat dari Preferences:");
  Serial.print("Analog A1: "); Serial.println(analogValueA1);
  Serial.print("Analog A2: "); Serial.println(analogValueA2);
  Serial.print("Digital S1: "); Serial.println(digitalStateS1);
  Serial.print("Digital S2: "); Serial.println(digitalStateS2);
  Serial.print("Digital R1: "); Serial.println(digitalStateR1);
  Serial.print("Digital R2: "); Serial.println(digitalStateR2);
  Serial.print("Digital RR1: "); Serial.println(digitalStateRR1);
  Serial.print("Digital RR2: "); Serial.println(digitalStateRR2);
  Serial.print("Interval ON: "); Serial.print(intervalminON); Serial.print(" min "); Serial.print(intervalsecON); Serial.println(" sec");
  Serial.print("Interval OFF: "); Serial.print(intervalminOFF); Serial.print(" min "); Serial.print(intervalsecOFF); Serial.println(" sec");
  Serial.print("Start Time: "); Serial.println(startTime);
  Serial.print("Stop Time: "); Serial.println(stopTime);
}

#endif
