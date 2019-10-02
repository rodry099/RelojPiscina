#ifndef FUNCIONES_H
#define FUNCIONES_H
#include "Arduino.h"

void configInicial();
void muestraPagina();
void arranqueNormal();
void arranqueNormalJson();
void guarda_config();
boolean reconnect();
void registerDevice(String);
void reloj();
void tomaHora(uint8_t[]);
void menuDisplay(int);
void seleccionMenu();
void programarCiclo();
void displayDiaHour(uint8_t[]);

//Rutinas Callbacks
void callback(char*, byte*, unsigned int);

#endif