#include <Arduino.h>
#include "Librerias.h"
#include "Globales.h"
#include "Funciones.h"

String diaSemana[] = {
    "Domingo",
    "Lunes",
    "Martes",
    "Miercoles",
    "Jueves",
    "Viernes",
    "Sabado"
    
};

void displayDiaHour(uint8_t horaDia[]){
    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(35+2,0);
    display.println(diaSemana[horaDia[0]]);

    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(35,14);
    display.print(horaDia[1]);
    display.print(":");
    if(horaDia[2]< 10){
       display.print("0"); 
    }
    display.print(horaDia[2]);


    display.display();
}