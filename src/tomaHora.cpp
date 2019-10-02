#include <Arduino.h>
#include "Librerias.h"
#include "Globales.h"
#include "Funciones.h"

#if defined(ESP8266)
#include <pgmspace.h>
#else
#include <avr/pgmspace.h>
#endif

void tomaHora(uint8_t horaDia[]){
    
    RtcDateTime now = Reloj.GetDateTime();
    horaDia[0] = uint8_t(now.DayOfWeek());
    horaDia[1] = uint8_t(now.Hour());
    horaDia[2] = uint8_t(now.Minute());
    Serial.print(now.Hour());
    Serial.print(":");
    Serial.print(now.Minute());
    Serial.println();
}