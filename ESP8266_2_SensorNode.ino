#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <DataManager.h>

DataManager dataManager;

void setup() {
    Serial.begin(115200);

    // Configuración WiFiManager
    WiFiManager wifiManager;
    wifiManager.autoConnect("SensorNodeAP");

    // Iniciar conexión WiFi
    Serial.println("Conectado a la red WiFi.");
}

void loop() {
    // Simular la lectura de sensores
    float temperatura = 36.5;
    float oxigenacion = 98.0;
    float ritmoCardiaco = 75.0;

    // Crear el payload
    String payload = "temp=" + String(temperatura) +
                     "&spo2=" + String(oxigenacion) +
                     "&bpm=" + String(ritmoCardiaco);

    // Enviar los datos al ESP8266 1
    dataManager.sendData(payload);

    delay(10000);  // Enviar cada 10 segundos
}
