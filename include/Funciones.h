#ifndef FUNCIONES_H
#define FUNCIONES_H
#include "Arduino.h"

void configInicial();
void muestraPagina();
void arranqueNormal();
void arranqueNormalJson();
void guarda_config();
void temporizador(uint8_t []);
bool reconnect();
void registerDevice(String);
void reloj();
void tomaHora(uint8_t[]);
void menuDisplay(int);
void seleccionMenu();
void programarCiclo(int);
void displayDiaHour(uint8_t[]);
void displayBloqProg(String, int, int[]);
void confirmarProg(int []);
void guardarProg(int []);
bool guardaProgramacion(String);
String matrizAjson(String, int []);
void leeProgramacion();
bool contador(long, long, int);
String controLuces();
String controlMotor();

//Rutinas Callbacks
void callback(char*, byte*, unsigned int);

#endif