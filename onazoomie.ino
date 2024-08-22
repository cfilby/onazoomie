#define LOGGING 1

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoHttpClient.h>

#include "arduino_secrets.h"
#include "ZoomAPI.h"

#define LED 13
#define POLLING_DELAY 15000


WiFiClientSecure wifiClient;
ZoomAPI zoomApi(wifiClient, ZOOM_ACCOUNT_ID, ZOOM_CLIENT_ID, ZOOM_CLIENT_SECRET);

void setup() {
  pinMode(LED, OUTPUT);

  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(1000);

  WiFi.setHostname("esp32-devkit");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.printf("\nConnecting to WiFi Network: %s\n", WIFI_SSID);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("\nConnected to the WiFi network");
  Serial.printf("Local ESP32 IP: %s\n", WiFi.localIP().toString());

  wifiClient.setInsecure();
}

void loop() {
  Serial.printf("loopStart: Free Heap: %d\n", ESP.getFreeHeap());
  Serial.println("Checking User Presence");
  zoomApi.getUserPresence(userMe);
  Serial.println();
  delay(POLLING_DELAY);
}
