#ifndef IO_H
#define IO_H

#include "pin_setup.h"
#include <Preferences.h>
//#include "DHT.h"
#include <light_CD74HC4067.h>
#include <Adafruit_INA219.h>

Preferences prefs;

Adafruit_INA219 ina219;

extern int t;
// Variabel global untuk menyimpan nilai analog dan digital
int analogValueA1, analogValueA2;
bool digitalStateS1, digitalStateS2;
bool digitalStateR1, digitalStateR2;
bool digitalStateRR1, digitalStateRR2;

// Variabel INA
float busVoltage, shuntVoltage, current;

// Variabel interval dan timer
int intervalOn, intervalOff;
bool isON = false; // Kondisi awal OFF
unsigned long previousMillis = 0; // Untuk tracking waktu
const int intervalUpdate = 1000; // Update setiap 1 detik


// Membaca tombol
int readButton() {
  return analogRead(BUTTON);
}

void inaSetup(){
  // Coba inisialisasi INA219
  if (!ina219.begin()) {
    Serial.println("Failed to find INA219 chip");
    return; // Keluar dari fungsi jika gagal
  }

}

void readIna219(){
// Read voltage and current from INA219.
  shuntVoltage = ina219.getShuntVoltage_mV();
  busVoltage = ina219.getBusVoltage_V();
  current = ina219.getCurrent_mA();
}

// // Switching
// void checkSwitch(){
//   String temp_source = "PSU";

//   prefs.begin("data", true);
//   String source = prefs.getString("source");
//   prefs.end();

//   prefs.begin("data", false); // false = Write mode
//   if (source == "Battery"){
//     if (busVoltage < 10){
//       temp_source = "PSU";
//       prefs.putString("source", temp_source);
//       setLED(1, false);
//     } else {

//     }
//   } else if (source == "PSU") {
//     if (busVoltage > 12){
//       temp_source = "Battery";
//       prefs.putString("source", temp_source);
//       setLED(1, true);
//   } else if (busVoltage < 10) {
//       temp_source = "PSU";
//       prefs.putString("source", temp_source);
//       setLED(1, false);
//   }

// }
// prefs.end();
// }

// Switching dengan Hysteresis
void checkSwitch() {
    static bool batteryLock = false;  // Status penguncian penggunaan PSU
    String temp_source = "PSU";

    // Ambil nilai terakhir dari penyimpanan
    prefs.begin("data", true);
    String source = prefs.getString("source");
    prefs.end();

    // Proses switching
    prefs.begin("data", false); // false = Write mode
    if (source == "Battery") {
        if (busVoltage < 10) {
            temp_source = "PSU";
            batteryLock = true; // Kunci agar tetap di PSU sampai 12V
            prefs.putString("source", temp_source);
            setLED(1, false);
        } else {
            temp_source = "Battery";
        }
    } else if (source == "PSU") {
        if (busVoltage > 12) {
            temp_source = "Battery";
            batteryLock = false; // Reset kunci saat beralih ke baterai
            prefs.putString("source", temp_source);
            setLED(1, true);
        } else if (busVoltage < 10) {
            temp_source = "PSU";
            batteryLock = true;
            prefs.putString("source", temp_source);
            setLED(1, false);
        } else if (busVoltage > 10 && !batteryLock) {
            temp_source = "Battery";
            prefs.putString("source", temp_source);
            setLED(1, true);
        }
    }
    prefs.end();
}


//setLED(0, true); // Menyalakan PIN 0

// Fungsi untuk mengontrol RR1 dengan countdown ON/OFF
void digitalRR1() {
  prefs.begin("data", true); // Read mode
  int setIntervalOn = prefs.getInt("pintervalON", 600);  // Default 10 menit
  int setIntervalOff = prefs.getInt("pintervalOFF", 600); // Default 10 menit
  prefs.end();

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= intervalUpdate) {
    previousMillis = currentMillis; // Reset timer

    if (isON) {
      intervalOn--;
      if (intervalOn <= 0) {
        isON = false;
        setLED(0, false);
        // setLED(1, false);
        setLED(2, false);
        setLED(3, false);
        intervalOn = setIntervalOn; // Reset interval ON
        intervalOff = setIntervalOff; // Reset interval OFF
        Serial.println("Pompa OFF");
      }
    } else {
      intervalOff--;
      if (intervalOff <= 0) {
        isON = true;
        setLED(0, true); //R2
        // setLED(1, false); //R1
        setLED(2, false); //s1
        setLED(3, false); //s2
        intervalOff = setIntervalOff; // Reset interval OFF
        intervalOn = setIntervalOn; // Reset interval ON
        Serial.println("Pompa ON");
      }
    }
  }
}

// Menampilkan output ke Serial Monitor
void writeOutput() {
  if (t % 5 == 0) {
  Serial.print("BUTTON VALUE: "); Serial.println(readButton());
  Serial.print("STATE: "); Serial.println(isON ? "ON" : "OFF");
  Serial.print("Time Left: "); Serial.println(isON ? intervalOn : intervalOff);
  Serial.print("ShuntVoltage: ");Serial.println(shuntVoltage);
  Serial.print("busVoltage: ");Serial.println(busVoltage);
  Serial.print("current: ");Serial.println(current);
  }
  checkSwitch();
  digitalRR1();

}

#endif
