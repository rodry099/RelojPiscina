#include <Arduino.h>
#include "Librerias.h"
#include "Globales.h"
#include "Funciones.h"

boolean reconnect() {
  willmsg = id_disp + "/status";
  String clientId = id_disp;
    if (client.connect(clientId.c_str(),willmsg.c_str(),1,0,"offline")) {
      Serial.println("connected");
      client.publish(willmsg.c_str(), "online");
      client.subscribe("device/setup");

      if(registrado > 0 ){
      String topicS = servidorNodeRed + "/" + categoria + "/" + id_disp + "/switch";
      client.subscribe(topicS.c_str());
      String topicF = servidorNodeRed + "/" + categoria + "/" + id_disp + "/feedback";
      client.subscribe(topicF.c_str());
      String topicP = servidorNodeRed + "/" + categoria + "/" + id_disp + "/Program";
      Serial.println(topicP);
      client.subscribe(topicP.c_str());
    }

  }
  return client.connected();
}
