#include <Arduino.h>
#include "Librerias.h"
#include "Globales.h"
#include "Funciones.h"

void programarCiclo(int bloqueProg){

    long ahora = 0, tiempoMaximo = 0;
    int arriba, abajo, izquierda, derecha, entrar, seleccion = 0;
    bool salir = false;
    int indice = 0;
    String bloque = "";

    int datosTemporales[13] = {};
        for(int i=0;i<13;i++){
            datosTemporales[i] = datosProgramador[i];
        }
    
    switch (bloqueProg)
    {
    case 1:
        bloque = "A";
        Serial.println("A");
        break;
    case 2:
        bloque = "B";
        indice += 3;
        Serial.println("B");
        break;
    
    default:
        break;
    }

    displayBloqProg(bloque,seleccion,datosTemporales);

    ahora = millis();
    tiempoMaximo = ahora;

    while(!salir){
        arriba = puertosI2c.read(4);
        delay(100);
        abajo = puertosI2c.read(5);
        delay(100);
        izquierda = puertosI2c.read(7);
        delay(100);
        derecha = puertosI2c.read(6);
        delay(100);
        entrar = puertosI2c.read(0);
        delay(100);
        ahora = millis();
        if(izquierda == 1){
            tiempoMaximo = ahora;
            if(seleccion > 0) seleccion--;
             displayBloqProg(bloque,seleccion, datosTemporales);
        }
        if(derecha == 1){
            tiempoMaximo = ahora;
            if(seleccion < 2) seleccion++;
             displayBloqProg(bloque, seleccion, datosTemporales);
        }

        if(arriba == 1 && seleccion == 0){
            tiempoMaximo = ahora;
            if(datosTemporales[indice+seleccion] > 0){
                datosTemporales[indice+seleccion]--;
                displayBloqProg(bloque,seleccion, datosTemporales);
            }
        }

        if(abajo == 1 && seleccion == 0){
            tiempoMaximo = ahora;
            if(datosTemporales[indice+seleccion] < 23){
                datosTemporales[indice+seleccion]++;
                displayBloqProg(bloque,seleccion, datosTemporales);
            }
        }

        if(arriba == 1 && seleccion == 1){
            tiempoMaximo = ahora;
            if(datosTemporales[indice+seleccion] > 0){
                datosTemporales[indice+seleccion]--;
                displayBloqProg(bloque,seleccion, datosTemporales);
            }
        }

        if(abajo == 1 && seleccion == 1){
            tiempoMaximo = ahora;
            if(datosTemporales[indice+seleccion] < 59){
                datosTemporales[indice+seleccion]++;
                displayBloqProg(bloque,seleccion, datosTemporales);
            }
        }

        if(arriba == 1 && seleccion == 2){
            tiempoMaximo = ahora;
            if(datosTemporales[indice+seleccion] > 0){
                datosTemporales[indice+seleccion]--;
                displayBloqProg(bloque,seleccion,datosTemporales);
            }
        }

        if(abajo == 1 && seleccion == 2){
            tiempoMaximo = ahora;
            if(datosTemporales[indice+seleccion] < 8){
                datosTemporales[indice+seleccion]++;
                displayBloqProg(bloque,seleccion, datosTemporales);
            }
        }

        if(entrar == 1){
           confirmarProg(datosTemporales);
           return;
        } 
       salir = contador(ahora, tiempoMaximo, 10000);
    }
}