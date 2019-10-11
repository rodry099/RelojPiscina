#include <Arduino.h>
#include "Librerias.h"
#include "Globales.h"
#include "Funciones.h"

void confirmarProg(int datos[]){

    long tiempoMaximo = 0;
    long ahora = 0;
    int ok, cancelar;
    bool salir = false;

    display.clearDisplay();
    display.setTextSize(1);            
    display.setTextColor(0,1);
    display.setCursor(8,32/2);             
    display.print("OK");
    display.setTextSize(1);            
    display.setTextColor(0,1);
    display.setCursor(128-56,32/2);             
    display.print("CANCEL");
    display.display();

    ahora = millis();
    tiempoMaximo = ahora;

    while (!salir)
    {
      ok = puertosI2c.read(7);
      delay(100);
      cancelar = puertosI2c.read(6);
      delay(100);
      ahora = millis();

        if(ok == 1){
            String json = matrizAjson("actualiza", datos);
            bool ok = guardaProgramacion(json);
            display.clearDisplay();
            display.setTextSize(1);            
            display.setTextColor(1,0);
            display.setCursor(8,32/2);
            if(ok) {
                display.print("OK DATOS GUARDADOS");
                client.publish("serverSwitch/piscina/piscina/confirmacion",json.c_str());
            }else display.print("Error al guardar");
            display.display();
            delay(2000);
            return;
        }
        if(cancelar == 1){
            display.clearDisplay();
            display.setTextSize(1);            
            display.setTextColor(1,0);
            display.setCursor(8,32/2);             
            display.print("Operacion Cancelada");
            display.display();
            delay(2000);
            return;
        }
        salir = contador(ahora, tiempoMaximo, 10000);
    }
    
}