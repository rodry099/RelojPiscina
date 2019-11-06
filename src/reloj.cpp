#include <Arduino.h>
#include "Librerias.h"
#include "Globales.h"
#include "Funciones.h"

#if defined(ESP8266)
#include <pgmspace.h>
#else
#include <avr/pgmspace.h>
#endif

void reloj(){    
    
    RtcDateTime dt = RtcDateTime(2019,10,1,17,3,00);
    
    if (!Reloj.IsDateTimeValid()) 
    {
        if (Reloj.LastError() != 0)
        {
            
            Serial.print("RTC communications error = ");
            Serial.println(Reloj.LastError());
        }
        else
        {
            
            Serial.println("RTC lost confidence in the DateTime!");
            Reloj.SetDateTime(dt);
        }
    }

    if (!Reloj.GetIsRunning())
    {
        Serial.println("RTC was not actively running, starting now");
        Reloj.SetIsRunning(true);
    }

    RtcDateTime now = Reloj.GetDateTime();
    if (now < dt) 
    {
        Serial.println("Reloj is older than compile time!  (Updating DateTime)");
        Reloj.SetDateTime(dt);
    }
    else if (now > dt) 
    {
        Serial.println("RTC is newer than compile time. (this is expected)");
    }
    else if (now == dt) 
    {
        Serial.println("RTC is the same as compile time! (not expected but all is fine)");
    }

    // never assume the Rtc was last configured by you, so
    // just clear them to your needed state
    Reloj.Enable32kHzPin(false);
    Reloj.SetSquareWavePin(DS3231SquareWavePin_ModeNone);
    Serial.print(now.Hour());
    Serial.print(":");
    Serial.println(now.Minute());
}