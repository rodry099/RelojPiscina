#include <Arduino.h>
#include "Librerias.h"
#include "Globales.h"
#include "Funciones.h"

void callback(char* topic, byte* payload, unsigned int length){

  const int capacity = JSON_OBJECT_SIZE(20);
  DynamicJsonBuffer DatosMqtt(capacity);
  char datos[length];
  unsigned int i=0;
  for (i=0;i<length;i++) {
    datos[i] = (char)payload[i];
  }

  Serial.println(datos);
  
  JsonObject& datosRecibidos = DatosMqtt.parseObject(datos);

      if (datosRecibidos.success()) {
         
        } else {
        //Serial.println("parseObject() FAILED");
        }
        String solicitud = datosRecibidos["solicitud"];
        String Stopic(topic);

        if(solicitud.equals("luces")){
          String estado = controLuces();
          client.publish("serverSwitch/piscina/piscina/confirmacion",estado.c_str());
        }

        if(solicitud.equals("motor")){
          String estado = controlMotor();
          client.publish("serverSwitch/piscina/piscina/confirmacion",estado.c_str());
        }

        if(solicitud.equals("guardar")){ 
          String datosAguardar = "", guardado = "", payload = "";
          datosRecibidos.remove("solicitud");
          datosRecibidos.printTo(datosAguardar);
          bool resultado = guardaProgramacion(datosAguardar);
          if(resultado) {
            guardado = "guardadoOk";
            leeProgramacion();
          }else guardado = "guardadoError";
          payload += "{\"";
          payload += "solicitud\":";
          payload += "\"";
          payload += guardado;
          payload +="\"}";
          client.publish("serverSwitch/piscina/piscina/confirmacion",payload.c_str());
        }

        if(solicitud.equals("datos")){
          leeProgramacion();
          String payload = matrizAjson("datos", datosProgramador);
          client.publish("serverSwitch/piscina/piscina/confirmacion",payload.c_str());
        }

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
