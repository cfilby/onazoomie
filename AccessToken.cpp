#include "AccessToken.h"
#include <ArduinoJson.h>

// Private Constructors
AccessToken::AccessToken() {}
AccessToken::AccessToken(String _tokenType, String _accessToken, int _expiresIn, String _scope)
  : tokenType(_tokenType), accessToken(_accessToken), expiresIn(_expiresIn), scope(_scope) {
  // TODO: Init Expiration Checker
}

// Public Methods
bool AccessToken::isValid() {
  return expiresIn != 0;
}

// Static Methods
AccessToken AccessToken::fromJsonResponse(String responseBody) {
  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, responseBody);
  if (error) {
    Serial.printf("Deserialization Failed: %s", error.c_str());
    return AccessToken();
  }

  return AccessToken(doc["token_type"], doc["access_token"], doc["expires_in"], doc["scope"]);
}