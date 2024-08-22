#include <iostream>
#include <ArduinoJson.h>

#include "ZoomAPI.h"
#include "arduino_secrets.h"


// Constructors
ZoomAPI::ZoomAPI(Client& _networkClient, String _accountId, String _clientId, String _clientSecret): 
  networkClient(_networkClient), accountId(_accountId), clientId(_clientId), clientSecret(_clientSecret), http(_networkClient, ZOOM_HOST, ZOOM_PORT) {
    //http.connectionKeepAlive();
  }

// Public Methods
void ZoomAPI::getUserPresence(String userId)
{
  AccessToken token = getAccessToken();
  if (!token.isValid()) {
    Serial.printf("getUserPresence: no valid token retrieved, skipping.");
    return;
  }
  http.beginRequest();
  http.get("/v2/users/" + userId + "/presence_status");
  http.sendHeader("Authorization", "Bearer " + token.accessToken);
  http.endRequest();
  
  // read the status code and body of the response
  int statusCode = http.responseStatusCode();
  long contentLength = http.contentLength();
  Serial.printf("ContentLength: %ld\n", contentLength);
  String responseBody = http.responseBody();
  if (statusCode != 200) {
    Serial.printf("Received unexpected status code on Check Presence: %d.", statusCode);
    if (!responseBody.isEmpty()) {
      Serial.printf("Response Body: %s", responseBody.c_str());
    }
    Serial.println();
    return;
  }

  if(responseBody.isEmpty()) {
    Serial.printf("No Response Body?\n");
    return;
  }

  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, responseBody);
  if (error) {
    Serial.printf("Deserialization Failed: %s", error.c_str());
    return;
  }
}

// Private Methods
AccessToken ZoomAPI::getAccessToken()
{
  if (!token.isValid()) {
    Serial.printf("Token Invalid, loading new token\n");
    token = fetchAccessToken();
  }
  Serial.printf("Token=%s\n", token.accessToken.c_str());
  return token;
}

AccessToken ZoomAPI::fetchAccessToken() {
  String postData = "grant_type=account_credentials&account_id=" + accountId;
  
  http.beginRequest();
  http.post("/oauth/token");
  http.sendHeader("Content-Type", "application/x-www-form-urlencoded");
  http.sendHeader("Content-Length", postData.length());
  http.sendBasicAuth(clientId.c_str(), clientSecret.c_str());
  http.beginBody();
  http.print(postData);
  http.endRequest();

  // read the status code and body of the response
  int statusCode = http.responseStatusCode();
  http.skipResponseHeaders();
  String responseBody = http.responseBody();
  if (statusCode != 200) {
    Serial.printf("Received unexpected status code on GetToken: %d. Response: %s\n", statusCode, responseBody.c_str());
    return AccessToken();
  }
  
  return AccessToken::fromJsonResponse(responseBody);
}



