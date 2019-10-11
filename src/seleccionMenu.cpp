#include <Arduino.h>
#include "Librerias.h"
#include "Globales.h"
#include "Funciones.h"

void seleccionMenu(){
    long ahora = 0, tiempoMaximo = 0;
    int arriba, abajo, atras, entrar, seleccion = 1;
    bool salir = false;

    ahora = millis();
    tiempoMaximo = ahora;

    while(salir == false){
        ahora = millis();
        arriba = puertosI2c.read(ARRIBA);
        delay(100);
        abajo = puertosI2c.read(ABAJO);
        delay(100);
        atras = puertosI2c.read(IZQUIERDA);
        delay(100);
        entrar = puertosI2c.read(ENTER);
        delay(100);
        if(arriba == 1){
            tiempoMaximo = ahora;
            if(seleccion > 1) seleccion--;
             menuDisplay(seleccion);
        }
        if(abajo == 1){
            tiempoMaximo = ahora;
            if(seleccion < 2) seleccion++;
             menuDisplay(seleccion);
        }
        if(atras == 1) return;

        if(entrar == 1){
            programarCiclo(seleccion);
            display.clearDisplay();
            display.display();
            return;
        } 
        salir = contador(ahora, tiempoMaximo, 10000);
    }
}