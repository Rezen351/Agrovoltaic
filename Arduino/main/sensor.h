#ifndef SENSOR_H
#define SENSOR_H
#include "DHT.h"
#include "motor.h"
#include "mqtt.h"


#define LDR1 34
#define LDR2 35
#define THRESHOLD 100  // Ambang batas perubahan nilai LDR

int prevLdr1 = 0, prevLdr2 = 0;  // Menyimpan nilai sebelumnya
bool isAutoMode = true;
String motorState = "STOP"; // Status awal motor

#define DHTPIN1 13
#define DHTPIN2 12
#define DHTTYPE DHT11

DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);

float temp1, hum1, temp2, hum2;

void setupSensorPV() {
  // Set LDR1, LDR2 as analog inputs
  pinMode(LDR1, INPUT);
  pinMode(LDR2, INPUT);

}


void readSensorPV() {
    int ldr1Value = analogRead(LDR1);  // Baca LDR1
    int ldr2Value = analogRead(LDR2);  // Baca LDR2

    // Cek apakah perubahan lebih besar dari threshold
    int change = abs(ldr1Value - prevLdr1);

    if (t % 5 == 0) {
        Serial.print("LDR1: "); Serial.println(ldr1Value);
        Serial.print("LDR2: "); Serial.println(ldr2Value);
    }

    // Hanya bergerak jika perubahan melebihi threshold
    if (change > THRESHOLD) {
        if (ldr1Value > ldr2Value) {
            moveUp();
        } else if (ldr2Value > ldr1Value) {
            moveDown();
        } else {
            stopMotor();
        }
    } else {
        stopMotor();
    }
    Serial.print("Change: "); Serial.println(change);
    // Simpan nilai LDR sebelumnya
    prevLdr1 = ldr1Value;
    prevLdr2 = ldr2Value;
}

// Fungsi mode manual (sesuai perintah dari Serial Monitor)
void controlMotorManually() {
    if (motorState == "UP") {
        moveUp();
    } else if (motorState == "DOWN") {
        moveDown();
    } else if (motorState == "STOP") {
        stopMotor();
    }
}

void autoManual(){
// Periksa apakah ada input dari Serial Monitor
    if (Serial.available() > 0) {
        String command = Serial.readStringUntil('\n'); // Baca input hingga newline
        command.trim(); // Hapus spasi ekstra

        if (command == "AUTO") {
            isAutoMode = true;
            Serial.println("Mode otomatis diaktifkan.");
        } else if (command == "UP") {
            isAutoMode = false;
            motorState = "UP";
        } else if (command == "DOWN") {
            isAutoMode = false;
            motorState = "DOWN";
        } else if (command == "STOP") {
            isAutoMode = false;
            motorState = "STOP";
        } else {
            Serial.println("Perintah tidak dikenal. Gunakan: AUTO, UP, DOWN, STOP.");
        }
    }

    // Jalankan sesuai mode atau status motor
    if (isAutoMode) {
        readSensorPV();
    } else {
        controlMotorManually();
    }

}



void setupDHT() {
    dht1.begin();
    dht2.begin();
}

void readDHT11() {
   if (t % 10 == 0){
    // Sensor 1: Suhu 27-28°C, Kelembaban 70-80%
    temp1 = random(270, 281) / 10.0;  // Menghasilkan angka antara 27.0 - 28.0
    hum1 = random(700, 801) / 10.0;  // Menghasilkan angka antara 70.0 - 80.0
    
    // Sensor 2: Suhu 25-26°C, Kelembaban 90-99%
    temp2 = random(250, 261) / 10.0;  // Menghasilkan angka antara 25.0 - 26.0
    hum2 = random(900, 1000) / 10.0; // Menghasilkan angka antara 90.0 - 99.9

   }
    // float temp1 = dht1.readTemperature();
    // float humi1 = dht1.readHumidity();
    // float temp2 = dht2.readTemperature();
    // float humi2 = dht2.readHumidity();

    // Buat objek JSON
    StaticJsonDocument<200> jsonDoc;
    jsonDoc["sensor1"]["temp"] = temp1;
    jsonDoc["sensor1"]["hum"] = hum1;
    jsonDoc["sensor2"]["temp"] = temp2;
    jsonDoc["sensor2"]["hum"] = hum2;

    // Serialize JSON ke string
    char jsonBuffer[256];
    serializeJson(jsonDoc, jsonBuffer);

    // Kirim JSON ke MQTT
    client.publish("AGROVOLTAIC/sensors", jsonBuffer);

    if (t % 5 == 0){
    Serial.print("Sensor 1 - Temperature: ");
    Serial.print(temp1);
    Serial.print(" °C, Humidity: ");
    Serial.print(hum1);
    Serial.println(" %");
    
    Serial.print("Sensor 2 - Temperature: ");
    Serial.print(temp2);
    Serial.print(" °C, Humidity: ");
    Serial.print(hum2);
    Serial.println(" %");

    Serial.println(jsonBuffer);
   }
    
}

#endif 
