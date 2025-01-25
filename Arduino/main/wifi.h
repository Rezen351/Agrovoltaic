#include <WiFi.h>

#define EAP_ANONYMOUS_IDENTITY "anonymous@tuke.sk"
#define EAP_IDENTITY "13322006@mahasiswa.itb.ac.id"
#define EAP_PASSWORD "Kyarajihan_152003"
#define EAP_USERNAME "13322006@mahasiswa.itb.ac.id"

const char* ssid = "eduroam";

void wifi_setup() {
  Serial.print(F("Connecting to network: "));
  Serial.println(ssid);
  WiFi.disconnect(true);
  WiFi.begin(ssid, WPA2_AUTH_PEAP, EAP_IDENTITY, EAP_USERNAME, EAP_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }

  Serial.println("");
  Serial.println(F("WiFi is connected!"));
  Serial.println(F("IP address set: "));
  Serial.println(WiFi.localIP());
}
