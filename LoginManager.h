#ifndef LOGIN_MANAGER_H
#define LOGIN_MANAGER_H

#include <ESP8266WebServer.h>

class LoginManager {
public:
    LoginManager();
    bool login(String username, String password);
    bool isAuthenticated();
    void logout();
    
private:
    int loginAttempts;
    bool authenticated;
};

#endif
