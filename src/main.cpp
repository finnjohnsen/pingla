#include <Arduino.h>
#include "web.h"

void setup() {
    Serial.begin(9600); 
    Serial.println("Setup");
    WEB::setup();
}

void loop() {}
