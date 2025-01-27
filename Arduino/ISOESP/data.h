#ifndef DATA_H
#define DATA_H

#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <esp_task_wdt.h>

// Deklarasi variabel eksternal
extern float humi1, temp1, humi2, temp2, humi3, temp3;
extern int analogValueA1, analogValueA2, digitalStateS1, digitalStateS2;
extern int setIntervalOff, setIntervalOn, intervalOff, intervalOn;
extern String startTime, stopTime;
extern PubSubClient client; // Pastikan `client` sudah dideklarasikan dan dikonfigurasi
void reconnect(); // Deklarasi fungsi untuk menghubungkan kembali ke broker MQTT
extern const char* deviceName;
extern const char* deviceModel;
// Tambahkan deklarasi global

void send_all_data() {
    Serial.println("Sending...");
    // Membuat JSON dengan ArduinoJson
    StaticJsonDocument<512> doc;
    // Sensor data
    JsonObject sensor1 = doc.createNestedObject("Sensor1");
    sensor1["Temperature"] = isnan(temp1) ? -404 : temp1;
    sensor1["Humidity"] = isnan(humi1) ? -404 : humi1;

    JsonObject sensor2 = doc.createNestedObject("Sensor2");
    sensor2["Temperature"] = isnan(temp2) ? -404 : temp2;
    sensor2["Humidity"] = isnan(humi2) ? -404 : humi2;

    JsonObject sensor3 = doc.createNestedObject("Sensor3");
    sensor3["Temperature"] = isnan(temp3) ? -404 : temp3;
    sensor3["Humidity"] = isnan(humi3) ? -404 : humi3;

    // Analog input
    JsonObject analogInput = doc.createNestedObject("AI");
    analogInput["AI1"] = analogValueA1;
    analogInput["AI2"] = analogValueA2;

    // Digital input
    JsonObject digitalInput = doc.createNestedObject("DI");
    digitalInput["DI1"] = digitalStateS1;
    digitalInput["DI2"] = digitalStateS2;

    // Digital output
    JsonObject digitalOutput = doc.createNestedObject("DO");
    digitalOutput["R1"] = digitalRead(R1);
    digitalOutput["R2"] = digitalRead(R2);
    digitalOutput["RR1"] = digitalRead(RR1);
    digitalOutput["RR2"] = digitalRead(RR2);

    // Serialisasi JSON ke buffer
    char jsonBuffer[512];
    size_t jsonLength = serializeJson(doc, jsonBuffer, sizeof(jsonBuffer));

    // Validasi ukuran JSON
    if (jsonLength >= sizeof(jsonBuffer)) {
        Serial.println("JSON terlalu besar untuk buffer.");
        return;
    }

    // Publikasi ke broker MQTT
    if (client.connected()) {
        const char* topic = "ISOESP/data";
        if (client.publish(topic, jsonBuffer)) {
            Serial.println("Pesan berhasil diterbitkan ke topik MQTT:");
        } else {
            Serial.println("Gagal menerbitkan pesan ke topik MQTT.");
        }
    } else {
        Serial.println("Koneksi MQTT terputus, mencoba menghubungkan kembali...");
        reconnect();
    }
    Serial.println(jsonBuffer);
    // Membuat JSON untuk informasi perangkat
    StaticJsonDocument<256> settingDoc;
    settingDoc["intervalOff"] = intervalOff;
    settingDoc["intervalOn"] = intervalOn;
    settingDoc["setIntervalOff"] = setIntervalOff;
    settingDoc["setIntervalOn"] = setIntervalOn;
    settingDoc["startTime"] = startTime;
    settingDoc["stopTime"] = stopTime;

    // Serialisasi JSON untuk informasi perangkat
    char settingBuffer[256];
    size_t settingLength = serializeJson(settingDoc, settingBuffer, sizeof(settingBuffer));

    // Validasi ukuran JSON
    if (settingLength >= sizeof(settingBuffer)) {
        Serial.println("JSON informasi perangkat terlalu besar untuk buffer.");
        return;
    }

    // Publikasi informasi perangkat ke broker MQTT
    const char* settingTopic = "ISOESP/setting";
    if (client.publish(settingTopic, settingBuffer)) {
        Serial.println("Setting perangkat berhasil diterbitkan ke MQTT:");
    } else {
        Serial.println("Gagal menerbitkan informasi perangkat ke MQTT.");
    }
    Serial.println(settingBuffer);

    // Membuat JSON untuk informasi perangkat
    StaticJsonDocument<256> infoDoc;
    infoDoc["DeviceName"] = deviceName;
    infoDoc["DeviceModel"] = deviceModel;
    infoDoc["IPAddress"] = WiFi.localIP().toString();
    infoDoc["Uptime"] = millis() / 1000; // Waktu aktif dalam detik
    infoDoc["CPUCore"] = xPortGetCoreID(); // Core ID tempat task dijalankan
    infoDoc["FreeHeap"] = ESP.getFreeHeap(); // Heap memory yang tersedia
    infoDoc["TaskCount"] = uxTaskGetNumberOfTasks(); // Jumlah task yang berjalan

    // Serialisasi JSON untuk informasi perangkat
    char infoBuffer[256];
    size_t infoLength = serializeJson(infoDoc, infoBuffer, sizeof(infoBuffer));

    // Validasi ukuran JSON
    if (infoLength >= sizeof(infoBuffer)) {
        Serial.println("JSON informasi perangkat terlalu besar untuk buffer.");
        return;
    }

    // Publikasi informasi perangkat ke broker MQTT
    const char* infoTopic = "ISOESP/info";
    if (client.publish(infoTopic, infoBuffer)) {
        Serial.println("Success sending info MQTT:");
    } else {
        Serial.println("Failed sending info to MQTT.");
    }
    Serial.println(infoBuffer);
    delay(1000);
}



#endif
