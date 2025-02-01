
#ifndef SENSOR_H
#define SENSOR_H

//unuseable pin, 4,12,13,14
#include <DHT.h> //library DHT

#define DHT1 12
#define DHT2 13
#define DHT3 14
#define DHTTYPE DHT11 // Tipe sensor DHT11

// Inisialisasi objek DHT untuk setiap sensor
DHT dht1(DHT1, DHTTYPE);
DHT dht2(DHT2, DHTTYPE);
DHT dht3(DHT3, DHTTYPE);

// Variabel untuk menyimpan data suhu dan kelembaban
float humi1, temp1;
float humi2, temp2;
float humi3, temp3;

void sensor_setup() {
  // Mulai sensor DHT
  dht1.begin();
  dht2.begin();
  dht3.begin();
}

void sensor_loop() {
  // Baca data dari sensor 1
  humi1 = dht1.readHumidity();
  temp1 = dht1.readTemperature();

  // Baca data dari sensor 2
  humi2 = dht2.readHumidity();
  temp2 = dht2.readTemperature();

  // Baca data dari sensor 3
  humi3 = dht3.readHumidity();
  temp3 = dht3.readTemperature();
}
#endif