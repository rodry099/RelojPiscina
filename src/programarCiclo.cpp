#include <Arduino.h>
#include "Librerias.h"
#include "Globales.h"
#include "Funciones.h"

void programarCiclo(int bloqueProg){

    long ahora = 0, tiempoMaximo = 0;
    int arriba, abajo, izquierda, derecha, entrar, posCursor = 0;
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

    displayBloqProg(bloque,posCursor,datosTemporales);

    ahora = millis();
    tiempoMaximo = ahora;

    while(!salir){
        arriba = puertosI2c.read(ARRIBA);
        delay(100);
        abajo = puertosI2c.read(ABAJO);
        delay(100);
        izquierda = puertosI2c.read(IZQUIERDA);
        delay(100);
        derecha = puertosI2c.read(DERECHA);
        delay(100);
        entrar = puertosI2c.read(ENTER);
        delay(100);
        ahora = millis();
        if(izquierda == 1){
            tiempoMaximo = ahora;
            if(posCursor > 0) posCursor--;
             displayBloqProg(bloque,posCursor, datosTemporales);
        }
        if(derecha == 1){
            tiempoMaximo = ahora;
            if(posCursor < 2) posCursor++;
             displayBloqProg(bloque, posCursor, datosTemporales);
        }

        if(arriba == 1 && posCursor == 0){
            tiempoMaximo = ahora;
            if(datosTemporales[indice+posCursor] > 0){
                datosTemporales[indice+posCursor]--;
                displayBloqProg(bloque,posCursor, datosTemporales);
            }
        }

        if(abajo == 1 && posCursor == 0){
            tiempoMaximo = ahora;
            if(datosTemporales[indice+posCursor] < 23){
                datosTemporales[indice+posCursor]++;
                displayBloqProg(bloque,posCursor, datosTemporales);
            }
        }

        if(arriba == 1 && posCursor == 1){
            tiempoMaximo = ahora;
            if(datosTemporales[indice+posCursor] > 0){
                datosTemporales[indice+posCursor]--;
                displayBloqProg(bloque,posCursor, datosTemporales);
            }
        }

        if(abajo == 1 && posCursor == 1){
            tiempoMaximo = ahora;
            if(datosTemporales[indice+posCursor] < 59){
                datosTemporales[indice+posCursor]++;
                displayBloqProg(bloque,posCursor, datosTemporales);
            }
        }

        if(arriba == 1 && posCursor == 2){
            tiempoMaximo = ahora;
            if(datosTemporales[indice+posCursor] > 0){
                datosTemporales[indice+posCursor]--;
                displayBloqProg(bloque,posCursor,datosTemporales);
            }
        }

        if(abajo == 1 && posCursor == 2){
            tiempoMaximo = ahora;
            if(datosTemporales[indice+posCursor] < 8){
                datosTemporales[indice+posCursor]++;
                displayBloqProg(bloque,posCursor, datosTemporales);
            }
        }

        if(entrar == 1){
           confirmarProg(datosTemporales);
           return;
        } 
       salir = contador(ahora, tiempoMaximo, 10000);
    }
}