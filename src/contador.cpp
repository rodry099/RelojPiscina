#include <Arduino.h>
#include "Librerias.h"
#include "Globales.h"
#include "Funciones.h"

bool contador(long ahora, long tiempoMaximo, int limite){

    if(ahora - tiempoMaximo > limite){
        display.clearDisplay();
        display.setTextSize(1);            
        display.setTextColor(1,0);
        display.setCursor(8,32/2);             
        display.print("Excedido Tiempo");
        display.display();
        return true;
        }
    return false;
}