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
    
    //--------RTC SETUP ------------
    // if you are using ESP-01 then uncomment the line below to reset the pins to
    // the available pins for SDA, SCL
    // Wire.begin(0, 2); // due to limited pins, use pin 0 and 2 for SDA, SCL
    
    RtcDateTime dt = RtcDateTime(2019,8,28,17,36,00);
    //printDateTime(compiled);
    Serial.println(dt);

    if (!Reloj.IsDateTimeValid()) 
    {
        if (Reloj.LastError() != 0)
        {
            // we have a communications error
            // see https://www.arduino.cc/en/Reference/WireEndTransmission for 
            // what the number means
            Serial.print("RTC communications error = ");
            Serial.println(Reloj.LastError());
        }
        else
        {
            // Common Causes:
            //    1) first time you ran and the device wasn't running yet
            //    2) the battery on the device is low or even missing

            Serial.println("RTC lost confidence in the DateTime!");

            // following line sets the RTC to the date & time this sketch was compiled
            // it will also reset the valid flag internally unless the Reloj device is
            // having an issue
            
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
}