#ifndef ZOOMAPI_H
#define ZOOMAPI_H

#include <Arduino.h>
#include <ArduinoHttpClient.h>
#include "AccessToken.h"

const String userMe = "me";

class ZoomAPI {
public:
  ZoomAPI(Client& _networkClient, String _accountId, String _clientId, String _clientSecret);
  void getUserPresence(String userId);

private:
  Client& networkClient;
  HttpClient http;
  String accountId;
  String clientId;
  String clientSecret;
  AccessToken token;

  // Returns the local access token if valid, otherwise fetches a fresh token
  AccessToken getAccessToken();

  // Get an AccessToken from Zoom's API
  AccessToken fetchAccessToken();
};
#endif