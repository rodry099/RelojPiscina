#include <Arduino.h>
#include "Librerias.h"
#include "Globales.h"
#include "Funciones.h"

WiFiClient espClient;
PubSubClient client(espClient);

long lastreconnectattempt = 0;
long anunciaDisposito = 0;

String id_disp = "";
int NumCanales;
String output = "";
String canal;
String willmsg; //topic direccion dispositivo
String ServerMqtt; // direccion del Brokker mqtt
String categoria; //categoria del dispositivo
String servidorNodeRed;
int registrado = 0;
int canalDispositivo;
const char* estadoDispositivo;

//Inicializacion Wifi **************
IPAddress ip(192, 168, 0, 1);
ESP8266WebServer server(80);
//WiFiServer servidor(8080);

/***************************************************
 * Inicializa PCF8574 para motor y las luces piscina
 ***************************************************/
PCF8574 relesPiscina(0x20);

/***************************************************
 * Declara reloj del sistema
 * ************************************************/
RtcDS3231<TwoWire> Reloj(Wire);

void setup() {
   Serial.begin(115200);
   Reloj.Begin(); // inicializa reloj del sistema
   relesPiscina.begin();
   relesPiscina.write8(B11111111);
   reloj();
   tomaHora();
   bool result = SPIFFS.begin();
   Serial.println("SPIFFS opened: " + result);

     File f = SPIFFS.open("/configuracion.txt", "r");
      if(!f){
        f.close();
        configInicial(); //inicia como AP y permite configurar conexion a router
      }

    // inicia normalmente conectando a la red que se haya configurado

    arranqueNormalJson();
    client.setServer(ServerMqtt.c_str(), 1883);
    client.setCallback(callback);
    
    lastreconnectattempt = 0;
    //NumCanales = registrado;
    if(registrado > 0){
      Serial.println("Dispositivo registrado en el sistema");
    }
}

void loop() {

    client.loop();
    delay(1);

 if (!client.connected()) {
    long now = millis();
    if(now - lastreconnectattempt >5000){
      lastreconnectattempt = now;
      if(reconnect()){
        lastreconnectattempt = 0;
      }
    }
  }

  if(registrado < NumCanales){
    long ahora = millis();
      if(ahora - anunciaDisposito > 5000){
        anunciaDisposito = ahora;
      client.publish("devices", output.c_str());
      Serial.println("Not registered");
      Serial.println(output);
    }
  }
  
}
