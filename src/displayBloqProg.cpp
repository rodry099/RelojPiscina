#include <Arduino.h>
#include "Librerias.h"
#include "Globales.h"
#include "Funciones.h"

void displayBloqProg(String bloque, int cursor, int datos[]){
    int indice = 0;
    if(bloque.equals("B")) indice += 3;

    display.clearDisplay();

    display.setTextSize(1);            
    display.setTextColor(0,1);
    display.setCursor(0,0);             
    display.print("SELECTED PROGRAM ");
    display.print(bloque);

    display.setTextColor(1,0);
    display.setTextSize(2);
    display.setCursor(0,14);

    if(cursor == 0) display.setTextColor(0,1);
    if(datos[indice] < 10) display.print("0");     
    display.print(datos[indice]);

    display.setTextColor(1,0);
    display.print(":");

    if(cursor == 1) display.setTextColor(0,1);
    if(datos[indice+1] < 10) display.print("0");
    display.print(datos[indice+1]);

    display.setTextColor(1,0);
    display.print(" ");

    if(cursor == 2) display.setTextColor(0,1);
    if(datos[indice+2] < 10) display.print("0");
    display.print(datos[indice+2]);

    display.setTextColor(1,0);
    display.print("hr");
    display.display();
}