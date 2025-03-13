#ifndef IO_H
#define IO_H

#include "pin_setup.h"
#include <Preferences.h>
#include "DHT.h"
#include <light_CD74HC4067.h>
#include <Adafruit_INA219.h>
#define DHTTYPE DHT11   // Menggunakan DHT11

CD74HC4067 mux(s0, s1, s2, s3); 
Preferences prefs;
DHT dht(sig, DHTTYPE);
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

//Variabel Multiplexer
//Channel
//0-2 Sensor
int sensorValues[3][2];
//
int muxValues[13];



// Membaca tombol
int readButton() {
  return analogRead(BUTTON);
}

// Memmbaca Sensor DHT

// Membaca Digital Input
void readMux(){
  for (int i = 0; i < 13; i++){
    mux.channel(i+3);
    muxValues[i] = analogRead(sig);
    delay(100);
  }
}

void dhtSetup(){
  dht.begin();
  }

 
void readDHT(int channel){
    // Tunggu beberapa detik antara pembacaan
  mux.channel(channel);
  // Baca kelembapan
  float h = dht.readHumidity();
  // Baca suhu dalam Celcius
  float t = dht.readTemperature();
  // Periksa apakah pembacaan berhasil
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // Cetak hasil ke Serial Monitor
  sensorValues[channel][0] = t;
  sensorValues[channel][1] = h;
  delay(100);
}

void inaSetup(){
  // Coba inisialisasi INA219
  if (!ina219.begin()) {
    Serial.println("Failed to find INA219 chip");
    return; // Keluar dari fungsi jika gagal
  }


void readIna219(){
// Read voltage and current from INA219.
  shuntVoltage = ina219.getShuntVoltage_mV();
  busVoltage = ina219.getBusVoltage_V();
  current = ina219.getCurrent_mA();
}

void readInput() {
//  readMux();
}

// Switching
void checkSwitch(){
  String temp_source = "PSU";

  prefs.begin("data", true);
  String source = prefs.getString("source");
  prefs.end();

  prefs.begin("data", false); // false = Write mode
  if (source == "Battery"){
    if (busVoltage < 10){
      temp_source = "PSU";
      prefs.putString("source", temp_source);
      setLED(1, false);
    } else {

    }
  } else if (source == "PSU") {
    if (busVoltage > 12){
      temp_source = "Battery";
      prefs.putString("source", temp_source);
      setLED(1, true);
  } else if (busVoltage < 10) {
      temp_source = "PSU";
      prefs.putString("source", temp_source);
      setLED(1, false);
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
      }
    }
  }
}

void readSensor(){
  for (int i = 0; i <= 2; i++) { // Membaca dari MUX 0 hingga 2
        readDHT(i);
        Serial.print(i);
        Serial.print(": Temperature: ");
        Serial.print(sensorValues[i][0]);
        Serial.print("°C, Humidity: ");
        Serial.print(sensorValues[i][1]);
        Serial.println("%");
    }
  }


void printArray() {
  Serial.print("Mux Values: ");
  for (int i = 0; i < 13; i++) {
    Serial.print(muxValues[i]);
    Serial.print(" ");
  }
  Serial.println(); // Pindah ke baris baru
}

// Menampilkan output ke Serial Monitor
void writeOutput() {
  if (t % 2 == 0) {
  Serial.print("BUTTON VALUE: "); Serial.println(readButton());
  Serial.print("STATE: "); Serial.println(isON ? "ON" : "OFF");
  Serial.print("Time Left: "); Serial.println(isON ? intervalOn : intervalOff);
  Serial.print("ShuntVoltage: ");Serial.println(shuntVoltage);
  Serial.print("busVoltage: ");Serial.println(busVoltage);
  Serial.print("current: ");Serial.println(current);
  printArray();
  }
  checkSwitch();
  digitalRR1();

}

#endif
