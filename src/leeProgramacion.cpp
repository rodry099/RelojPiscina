#include <Arduino.h>
#include "Librerias.h"
#include "Globales.h"
#include "Funciones.h"

void leeProgramacion(){
    File programa = SPIFFS.open("/programacion.txt", "r");
   if(!programa){
     Serial.println("No existe el archivo");
     programa.close();
     return;
   }
     StaticJsonBuffer<512> jsonBuffer;
     JsonObject& progJson = jsonBuffer.parseObject(programa);
    progJson.prettyPrintTo(Serial);
     datosProgramador[0] = progJson["horaA"][0];
     datosProgramador[1] = progJson["horaA"][1];
     datosProgramador[2] = progJson["horaA"][2];
     /******************************************/
     datosProgramador[3] = progJson["horaB"][0];
     datosProgramador[4] = progJson["horaB"][1];
     datosProgramador[5] = progJson["horaB"][2];
     /*******************************************/
     datosProgramador[6] = progJson["diaSemana"][0];
     datosProgramador[7] = progJson["diaSemana"][1];
     datosProgramador[8] = progJson["diaSemana"][2];
     datosProgramador[9] = progJson["diaSemana"][3];
     datosProgramador[10] = progJson["diaSemana"][4];
     datosProgramador[11] = progJson["diaSemana"][5];
     datosProgramador[12] = progJson["diaSemana"][6];
}