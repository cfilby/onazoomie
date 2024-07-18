#ifndef ACCESSTOKEN_H
#define ACCESSTOKEN_H

#include <Arduino.h>

class AccessToken
{
  public:
    String tokenType;
    String accessToken;
    int expiresIn;
    String scope;

    AccessToken();
    AccessToken(String _tokenType, String _accessToken, int _expiresIn, String _scope);

    bool isValid();
    static AccessToken fromJsonResponse(String responseBody);
};
#endif