#include <Arduino.h>
#include "Librerias.h"
#include "Globales.h"
#include "Funciones.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

WiFiClient espClient;
PubSubClient client(espClient);
long leeHora = 0;
long lecturaTecla = 0;
long lastreconnectattempt = 0;
long anunciaDisposito = 0;

int NumCanales;
uint8_t horaYdia[3] = {0,0,0};

String id_disp = "";
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
   Wire.begin(0,2); // para Esp-01 SDA = 0 , SCL = 2;

   // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
  }
   Reloj.Begin(); // inicializa reloj del sistema
   relesPiscina.begin();
   relesPiscina.write8(B11111111);
   reloj();
   tomaHora(horaYdia);
   bool result = SPIFFS.begin();
   Serial.println("SPIFFS opened: " + result);

     File f = SPIFFS.open("/configuracion.txt", "r");
      if(!f){
        f.close();
        configInicial(); //inicia como AP y permite configurar conexion a router
      }

    // inicia normalmente conectando a la red que se haya configurado

    arranqueNormalJson();
    display.display();
    client.setServer(ServerMqtt.c_str(), 1883);
    client.setCallback(callback);
    
    lastreconnectattempt = 0;
    //NumCanales = registrado;
    if(registrado > 0){
      Serial.println("Dispositivo registrado en el sistema");
    }
}

void loop() {
    
 if (!client.connected()) {
    long now = millis();
    if(now - lastreconnectattempt > 5000){
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
  long tempoTecla = millis();
  if(tempoTecla - lecturaTecla > 1000){
    lecturaTecla = tempoTecla;
    int tecla = relesPiscina.read(0);
    if( tecla == 1){
      menuDisplay(1);
      seleccionMenu();
      tomaHora(horaYdia);
      displayDiaHour(horaYdia);
    }
  }

  long tempoHora = millis();
  if(tempoHora - leeHora > 60000){
    leeHora = tempoHora;
    tomaHora(horaYdia);
    displayDiaHour(horaYdia);
  }

    client.loop();
    delay(1);

}
