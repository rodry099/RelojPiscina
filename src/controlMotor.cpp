#include <Arduino.h>
#include "Librerias.h"
#include "Globales.h"
#include "Funciones.h"

String controlMotor(){
    String estadoChar = "";
    String json = "";
    int estado = puertosI2c.read(MOTOR_PISCINA);
    if(estado == 0) {
        estadoChar = "off";
        puertosI2c.write(MOTOR_PISCINA, 1);
    }
    if(estado == 1) {
        estadoChar = "on";
        puertosI2c.write(MOTOR_PISCINA, 0);
    }
    json += "{\"motor\":\"";
    json += estadoChar;
    json += "\"}";
    return json;
}