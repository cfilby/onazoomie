#include "ZoomAPI.h"
#include <iostream>

// Constructors
ZoomAPI::ZoomAPI(HttpClient _http, String _accountId, String _clientId, String _clientSecret): 
  http(_http), accountId(_accountId), clientId(_clientId), clientSecret(_clientSecret) {}

// Public Methods
void ZoomAPI::getUserPresence(String userId)
{
  token = getAccessToken();
  http.beginRequest();
  http.get("/users/" + userId + "/presence_status");
  http.sendHeader("Authorization", "Bearer " + token.accessToken);
  http.endRequest();

  // read the status code and body of the response
  int statusCode = http.responseStatusCode();
  String responseBody = http.responseBody();
  if (statusCode != 200) {
    Serial.printf("Received unexpected status code on getUserPresence: %d. Response: %s", statusCode, responseBody);
    return;
  }
  
  Serial.printf("Status: %s", responseBody);
}

// Private Methods
AccessToken ZoomAPI::getAccessToken()
{
  if (!token.isValid()) {
    Serial.printf("Token Invalid, loading new token");
    token = fetchAccessToken();
  }
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
  String responseBody = http.responseBody();
  if (statusCode != 200) {
    Serial.printf("Received unexpected status code on GetToken: %d. Response: %s", statusCode, responseBody);
    return AccessToken();
  }
  
  return AccessToken::fromJsonResponse(responseBody);
}



