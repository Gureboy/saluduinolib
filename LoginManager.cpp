#include "LoginManager.h"

LoginManager::LoginManager() : loginAttempts(0), authenticated(false) {}

bool LoginManager::login(String username, String password) {
    if (username == "Saluduino" && password == "SaluduinoWeb") {
        authenticated = true;
        loginAttempts = 0;
        return true;
    } else {
        loginAttempts++;
        if (loginAttempts >= 5) {
            // Bloquear después de 5 intentos
            delay(30000);  // Bloqueo de 30 segundos
        }
        return false;
    }
}

bool LoginManager::isAuthenticated() {
    return authenticated;
}

void LoginManager::logout() {
    authenticated = false;
}
