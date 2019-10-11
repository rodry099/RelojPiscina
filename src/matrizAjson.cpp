#include <Arduino.h>
#include "Librerias.h"
#include "Globales.h"
#include "Funciones.h"

String matrizAjson(String respuesta, int matriz[]){
    int luz = 1, motor = 1;
    String json = "";
    String estadoLuz = "", estadoMotor = "";
    DynamicJsonBuffer jb;

    JsonObject& prog = jb.createObject();

    luz = puertosI2c.read(LUCES_PISCINA);
    delay(100);
    motor = puertosI2c.read(MOTOR_PISCINA);

    estadoLuz = (luz == 1)? "off":"on";
    estadoMotor = (motor == 1)? "off":"on";

    prog["solicitud"] = respuesta;
    prog["luces"] = estadoLuz;
    prog["motor"] = estadoMotor;

    JsonArray& horaA = prog.createNestedArray("horaA");
    horaA.add(matriz[0]);
    horaA.add(matriz[1]);
    horaA.add(matriz[2]);

    JsonArray& horaB = prog.createNestedArray("horaB");
    horaB.add(matriz[3]);
    horaB.add(matriz[4]);
    horaB.add(matriz[5]);

    JsonArray& diaSemana = prog.createNestedArray("diaSemana");
    diaSemana.add(matriz[6]);
    diaSemana.add(matriz[7]);
    diaSemana.add(matriz[8]);
    diaSemana.add(matriz[9]);
    diaSemana.add(matriz[10]);
    diaSemana.add(matriz[11]);
    diaSemana.add(matriz[12]);

    prog.printTo(json);
    Serial.println(json);
    return json;
}