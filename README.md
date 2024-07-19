# OnAZoomie

An Arduino IDE based project for the ESP32 to display whether or not the configured user is actively in a Zoom Meeting. There are simpler ways to do this, but this is meant to be a fun exploration of C++, Electronics and Embedded Development.

### Specifying Config and Secrets

To build this project, you will need to create an `arduino_secrets.h` file that defines the following macros.

```cpp
// WiFi Credentials
#define SECRET_WIFI_SSID "SSIDHere"
#define SECRET_WIFI_PASSWORD "PasswordHere"

// Zoom OAuth Credentials
#define ACCOUNT_ID "ZoomAccountID"
#define CLIENT_ID "ZoomClientID"
#define CLIENT_SECRET "ZoomClientSecret"
```