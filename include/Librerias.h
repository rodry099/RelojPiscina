#ifndef LIBRERIAS_H
#define LIBRERIAS_H
    #include <Arduino.h>
    #include <ESP8266WiFi.h>
    #include <WiFiClient.h>
    #include <ESP8266WebServer.h>
    #include <FS.h>
    #include <Wire.h>
    #include "PCF8574.h"
    #include <PubSubClient.h>
    #include <ArduinoJson.h>

    //declaracion de objetos sin inicializar
    //inicializar solo una vez en cualquier lugar
    extern WiFiClient espClient;
    extern PubSubClient client;
    extern IPAddress ip;
    extern ESP8266WebServer server;
    extern PCF8574 relesPiscina;
    
#endif