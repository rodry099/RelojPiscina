#include <Arduino.h>
#include "Librerias.h"
#include "Globales.h"
#include "Funciones.h"

void callback(char* topic, byte* payload, unsigned int length){

  String estadoDevuelto = "";
  String solicitud = servidorNodeRed + "/" + categoria + "/" + id_disp + "/feedback";
  String respuestaEstado = servidorNodeRed + "/estadoDispositivos";

  const int capacity = JSON_OBJECT_SIZE(4);
  StaticJsonBuffer<capacity> DatosMqtt;
  char datos[80];
  unsigned int i=0;
  for (i=0;i<length;i++) {
    datos[i] = (char)payload[i];
  }
  JsonObject& obj = DatosMqtt.parseObject(datos);

      if (obj.success()) {
          //Serial.println("parseObject() succeeded");
        } else {
        //Serial.println("parseObject() FAILED");
        }
        
        String Stopic(topic);

        const char* dias = obj["dias"];
        const char* horaInicio = obj["horaInicio"];

        Serial.println(dias);
        Serial.println(horaInicio);

    /***************************************
      si recibe el topic device/setup
      llama a la subrutina registerDevices
      y guarda 1 en la variable registrado
      del archivo configuracion
    ***************************************/
    if(Stopic.equals("device/setup")){
      registerDevice(estadoDispositivo);
      registrado = 1;
      anunciaDisposito = 0;
      ESP.restart();
      return;
    }

}
