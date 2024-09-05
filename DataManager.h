#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include <ESP8266WebServer.h>

class DataManager {
public:
    void sendData(const String& data);
    void handleIncomingData(ESP8266WebServer& server);
};

#endif
