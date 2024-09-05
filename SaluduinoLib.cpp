#include "SaluduinoLib.h"

SaluduinoLib::SaluduinoLib() : server(80), loginManager(), pageManager(), dataManager() {}

void SaluduinoLib::begin() {
    // Configurar WiFiManager
    wifiManager.autoConnect("SaluduinoAP");

    // Configurar rutas de páginas
    pageManager.setupPages(server, loginManager);

    // Iniciar servidor web
    server.begin();
}

void SaluduinoLib::handleClient() {
    server.handleClient();
}
