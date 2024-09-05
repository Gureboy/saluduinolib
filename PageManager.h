#ifndef PAGE_MANAGER_H
#define PAGE_MANAGER_H

#include <ESP8266WebServer.h>
#include "LoginManager.h"

class PageManager {
public:
    void setupPages(ESP8266WebServer& server, LoginManager& loginManager);
};

#endif
