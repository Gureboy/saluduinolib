#ifndef SALUDUINO_LIB_H
#define SALUDUINO_LIB_H

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include "LoginManager.h"
#include "PageManager.h"
#include "DataManager.h"

class SaluduinoLib {
public:
    SaluduinoLib();
    void begin();
    void handleClient();

private:
    ESP8266WebServer server;
    LoginManager loginManager;
    PageManager pageManager;
    DataManager dataManager;
    WiFiManager wifiManager;
};

#endif
