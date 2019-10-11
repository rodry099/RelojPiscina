#include <Arduino.h>
#include "Librerias.h"
#include "Globales.h"
#include "Funciones.h"

bool guardaProgramacion(String programacion){

    Serial.println(programacion);

    //abrir archivo programcion txt modo escritura

    SPIFFS.remove("/programacion.txt");
    
    File progTemp = SPIFFS.open("/programacion.txt", "w");
        if(!progTemp){
            Serial.println("No existe el archivo");
            progTemp.close();
            return false;
        }

    //guardar json en programacion.txt

    progTemp.print(programacion);

    //cerrar archivo

    progTemp.close();
    return true;
}