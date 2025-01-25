#include <DHT.h>

#define DHT1 12
#define DHT2 13
#define DHT3 14
#define DHTTYPE DHT11

extern float humi1, temp1, humi2, temp2, humi3, temp3;

DHT dht1(DHT1, DHTTYPE);
DHT dht2(DHT2, DHTTYPE);
DHT dht3(DHT3, DHTTYPE);

void sensor_setup() {
  dht1.begin();
  dht2.begin();
  dht3.begin();
  Serial.println("Monitoring Suhu dan Kelembaban dengan 3 Sensor DHT11");
}

void sensor_loop() {
  humi1 = dht1.readHumidity();
  temp1 = dht1.readTemperature();
  humi2 = dht2.readHumidity();
  temp2 = dht2.readTemperature();
  humi3 = dht3.readHumidity();
  temp3 = dht3.readTemperature();

  if (isnan(humi1) || isnan(temp1)) {
    Serial.println("Sensor 1 tidak terbaca...");
  } else {
    Serial.print("Sensor 1 -> Suhu: ");
    Serial.print(temp1);
    Serial.print(" C, Kelembaban: ");
    Serial.print(humi1);
    Serial.println(" %RH");
  }

  if (isnan(humi2) || isnan(temp2)) {
    Serial.println("Sensor 2 tidak terbaca...");
  } else {
    Serial.print("Sensor 2 -> Suhu: ");
    Serial.print(temp2);
    Serial.print(" C, Kelembaban: ");
    Serial.print(humi2);
    Serial.println(" %RH");
  }

  if (isnan(humi3) || isnan(temp3)) {
    Serial.println("Sensor 3 tidak terbaca...");
  } else {
    Serial.print("Sensor 3 -> Suhu: ");
    Serial.print(temp3);
    Serial.print(" C, Kelembaban: ");
    Serial.print(humi3);
    Serial.println(" %RH");
  }

  Serial.println("---------------------------------");
}
