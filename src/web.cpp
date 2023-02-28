#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include "ESPAsyncWebServer.h"
#include "LittleFS.h"

namespace WEB {
    AsyncWebServer server(80);

    const char* ssid = "pingla";
    const char* password = "pingla";
    IPAddress local_IP(192,168,4,1);
    IPAddress gateway(192,168,4,254);
    IPAddress subnet(255,255,255,0);

    void notFound(AsyncWebServerRequest *request) {
        request->send(404, "text/plain", "Not found");
    }

    void setup() {
        Serial.print("Setting soft-AP configuration ... ");
        Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");
        Serial.print("Setting soft-AP ... ");
        Serial.println(WiFi.softAP(ssid) ? "Ready" : "Failed!");

        Serial.print("Soft-AP IP address = ");
        Serial.println(WiFi.softAPIP());
        LittleFS.begin();

        server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
            File file = LittleFS.open("/www/index.html", "r");
            request->send(200, "text/html;charset=utf-8", file.readString());
            file.close();
        });

        server.on("/main.js", HTTP_GET, [](AsyncWebServerRequest *request){
            File file = LittleFS.open("/www/main.js", "r");
            request->send(200, "text/javascript; charset=utf-8", file.readString());
            file.close();
        });
        server.onNotFound(notFound);
        server.begin();
        Serial.print("Pingla er klar");
    }
}
