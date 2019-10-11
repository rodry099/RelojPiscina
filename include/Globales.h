#include <Arduino.h>

#ifndef GLOBALES_H
#define GLOBALES_H

//Variables **********************
#define LUCES_PISCINA 2
#define MOTOR_PISCINA 3

extern long lastreconnectattempt;
extern long anunciaDisposito;

extern String id_disp;
extern int NumCanales;
extern String output;
extern String canal;
extern String willmsg; //topic direccion dispositivo
extern String ServerMqtt; // direccion del Brokker mqtt
extern String categoria; //categoria del dispositivo
extern String servidorNodeRed;
extern int datosProgramador[];
extern int registrado;
extern int canalDispositivo;
extern const char* estadoDispositivo;

#endif