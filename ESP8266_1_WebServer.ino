#include <SaluduinoLib.h>

SaluduinoLib saluduino;

void setup() {
    Serial.begin(115200);
    saluduino.begin();
}

void loop() {
    saluduino.handleClient();
}
