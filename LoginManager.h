#ifndef LOGIN_MANAGER_H
#define LOGIN_MANAGER_H

#include <ESP8266WebServer.h>

class LoginManager {
public:
    LoginManager();
    void readPage();
    bool login(const String& username, const String& password);
    bool isAuthenticated() const;
    void logout();
    
private:
    int loginAttempts;
    bool authenticated;
};

#endif
