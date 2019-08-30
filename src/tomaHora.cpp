#include <Arduino.h>
#include "Librerias.h"
#include "Globales.h"
#include "Funciones.h"

#if defined(ESP8266)
#include <pgmspace.h>
#else
#include <avr/pgmspace.h>
#endif

void tomaHora(){
    
    RtcDateTime now = Reloj.GetDateTime();
    Serial.print(now.Hour());
    Serial.print(":");
    Serial.print(now.Minute());
    Serial.println();
}