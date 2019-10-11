#include <Arduino.h>
#include "Librerias.h"
#include "Globales.h"
#include "Funciones.h"

String controLuces(){
    String estadoChar = "";
    String json = "";
    int estado = puertosI2c.read(LUCES_PISCINA);
    if(estado == 0) {
        estadoChar = "off";
        puertosI2c.write(LUCES_PISCINA, 1);
    }
    if(estado == 1) {
        estadoChar = "on";
        puertosI2c.write(LUCES_PISCINA, 0);
    }
    json += "{\"luces\":\"";
    json += estadoChar;
    json += "\"}";
    return json;
}