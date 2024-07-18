#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoHttpClient.h>

#include "arduino_secrets.h"
#include "ZoomAPI.h"

#define LED 13
#define POLLING_DELAY 15000

WiFiClientSecure wifiClient;
HttpClient httpClient(wifiClient, "zoom.us", 443);
ZoomAPI zoomApi(httpClient, ACCOUNT_ID, CLIENT_ID, CLIENT_SECRET);

void setup() {
  pinMode(LED, OUTPUT);

  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(1000);

  WiFi.setHostname("esp32-devkit");
  WiFi.mode(WIFI_STA);
  WiFi.begin(SECRET_WIFI_SSID, SECRET_WIFI_PASSWORD);
  Serial.println("\nConnectingi WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());

  // TODO: Confirm this is needed
  wifiClient.setInsecure();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Checking User Presence");
  zoomApi.getUserPresence(userMe);
  delay(POLLING_DELAY);
}
