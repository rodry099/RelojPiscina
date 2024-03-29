#include <Arduino.h>
#include "Librerias.h"
#include "Globales.h"
#include "Funciones.h"

void menuDisplay(int seleccion){

    int color = 1, colorA = 1, colorB = 1;
    int fondoA = 0, fondoB = 0;
    if(seleccion == 1){
        colorA = 0;
        fondoA = 1;
    }
    if(seleccion == 2){
        colorB = 0;
        fondoB = 1;
    }
    display.clearDisplay();

    display.setTextSize(1);            
    display.setTextColor(color);
    display.setCursor(0,0);             
    display.println(F("SELECT PROGRAM"));

    display.setTextSize(1);            
    display.setTextColor(colorA,fondoA);
    display.setCursor(0,12);             
    display.println(F("PROGRAM A"));

    display.setTextSize(1);            
    display.setTextColor(colorB,fondoB);
    display.setCursor(0,24);             
    display.println(F("PROGRAM B"));

    display.display();
}