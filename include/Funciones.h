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
void tomaHora();

//Rutinas Callbacks
void callback(char*, byte*, unsigned int);

#endif