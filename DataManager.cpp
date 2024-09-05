#include "DataManager.h"
#include <ESP8266HTTPClient.h>

void DataManager::sendData(const String& data) {
    HTTPClient http;
    http.begin("http://<ESP8266_1_IP>/sensorData");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpResponseCode = http.POST(data);
    http.end();
}

void DataManager::handleIncomingData(ESP8266WebServer& server) {
    server.on("/sensorData", HTTP_POST, [&]() {
        String temp = server.arg("temp");
        String spo2 = server.arg("spo2");
        String bpm = server.arg("bpm");

        // Procesar y guardar los datos recibidos
        Serial.println("Datos recibidos: " + temp + ", " + spo2 + ", " + bpm);

        server.send(200, "text/plain", "Datos recibidos");
    });
}
