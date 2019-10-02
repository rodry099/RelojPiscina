#include <Arduino.h>
#include "Librerias.h"
#include "Globales.h"
#include "Funciones.h"

void seleccionMenu(){
    int arriba, abajo, atras, entrar, seleccion = 1;
    bool salir = false;

    while(salir == false){
        arriba = relesPiscina.read(4);
        delay(100);
        abajo = relesPiscina.read(5);
        delay(100);
        atras = relesPiscina.read(7);
        delay(100);
        entrar = relesPiscina.read(0);
        delay(100);
        if(arriba == 1){
            if(seleccion > 1) seleccion--;
             menuDisplay(seleccion);
        }
        if(abajo == 1){
            if(seleccion < 2) seleccion++;
             menuDisplay(seleccion);
        }
        if(atras == 1) salir = true;

        if(entrar == 1){
            programarCiclo();
            salir = true;
        } 
        delay(100);
    }
}