//*******************************************
//Programa del proyecto ESP32 AdminTool
//    03/02/2023
//*******************************************

#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient mqttclient(espClient);

char topico[150];
String mqtt_data = "";
long lastMqttReconnectAttempt   = 0;
long lastMsg = 0;
void callback(char *topic, byte *payload, unsigned int length);
String Json();

//---------------------------------
// MQTT Connect
//-----------------------------------  
bool mqtt_connect(){
    mqttclient.setServer(mqtt_server, mqtt_port);
    mqttclient.setCallback(callback);
    log("Info: Intentando conexión al Broker MQTT...");
    //Conexión al SErvido MQTT, ClientID, Usuario, Password
    //Ver documentación => pubsubclient de Knolleary
    if (mqttclient.connect(mqtt_id, mqtt_user, mqtt_passw))
    {
        log("Info: Conectando al Broker MQTT");
        //Nos suscribimos a comandos Topicos: usuarios/dispositivo/comando
        String topico_suscribe = String(mqtt_user) + "/"+ mqtt_id + "/command";
        topico_suscribe.toCharArray(topico, 150);
        mqttclient.subscribe(topico);
        topico_suscribe.toCharArray(topico, 150);
        mqttclient.publish(topico, "ok"); //publicar rspuesta ok por MQTT
        log("Topico: " + topico_suscribe);
    } else
    {
        log("Error: failed, rc= " + mqttclient.state());
        return(0);
    } 
   return(1);    
}
//---------------------------------
// Función JSON con información de envío por MQTT
//----------------------------------- 
String Json(){
    String response;
    DynamicJsonDocument jsonDoc(3000);
    jsonDoc["WFDBM"] = WiFi.status() == WL_CONNECTED ? String(WiFi.RSSI()) : F("0");
    jsonDoc["WFPRC"] = WiFi.status() == WL_CONNECTED ? String(getRSSIasQuality(WiFi.RSSI())) : F("0");
    jsonDoc["TempCPU"] = String(TempCPUValue());
    jsonDoc["RAMD"] = String(ESP.getFreeHeap()* 100 / ESP.getHeapSize());
    jsonDoc["FLASHU"] = String(round(SPIFFS.usedBytes() * 100 / SPIFFS.totalBytes()), 0);
    jsonDoc["relay1_status"] = String(Relay01_status ? "true" : "false");
    jsonDoc["relay2_status"] = String(Relay02_status ? "true" : "false");
    serializeJson(jsonDoc, response);
    return response;
}
//---------------------------------
// Manejo de los mensajes salientes
//----------------------------------- 
void mqtt_publish(){   
    String topic = String(mqtt_user) + "/" +mqtt_id + "/values";
    mqtt_data = Json();
    mqttclient.publish(topic.c_str(), mqtt_data.c_str());
    //TODO: Borrar salida para verificar la publicación
    log("Publicacion realizada de values");
    mqtt_data = "";
    mqttTX();
} 
//---------------------------------
// Manejo de los mensajes entrantes
//-----------------------------------  
void callback(char *topic, byte *payload, unsigned int length){
    String mensaje = "";
    String str_topic(topic);

    for (uint16_t i = 0; i < length; i++)
    {
        mensaje += (char)payload[i];
        mqttRX();
    }

    mensaje.trim();
    DynamicJsonDocument jsonDoc(300);
    deserializeJson(jsonDoc, mensaje);
    //Manejo de acciones al llegar un dato json
    if (jsonDoc["RELAY1"] == "on")
    {
        setOnSingle(RELAY1);
        Relay01_status = HIGH;
        settingsSaveRelays();
    }else if (jsonDoc["RELAY1"] == "off")
        {
            setOffSingle(RELAY1);
            Relay01_status = LOW;
            settingsSaveRelays();
        }else if (jsonDoc["RELAY2"] == "on")
            {
                setOnSingle(RELAY2);
                Relay02_status = HIGH;
                settingsSaveRelays();
            }else if (jsonDoc["RELAY2"] == "off")
                {
                    setOffSingle(RELAY2);
                    Relay02_status = LOW;
                    settingsSaveRelays();
                }

    


    log("Info: Topico -->" + str_topic);
    log("Info: Mensaje -->" + mensaje);
    serializeJsonPretty(jsonDoc, Serial);
}


void mqttLoop(){
    if (mqtt_enable)
    {
        if (!mqttclient.connected())
        {
            long now = millis();
            //intenta y reconecta continuamente por los primeros 60 s despues intenta cada 120s
            if ((now < 60000) || ((now - lastMqttReconnectAttempt) > 120000))
            {
                lastMqttReconnectAttempt = now;
                if (mqtt_connect())
                {   //Intenta reconectar
                    lastMqttReconnectAttempt = 0;
                }
                //Poner en ON el led del MQTT
                setOnSingle(MQTTLED);
            }
        } else
            {  // SI EL MQTT CONECTA
                mqttclient.loop();
                //Poner en OFF el led del MQTT
                setOffSingle(MQTTLED);
            }      
    }
}
