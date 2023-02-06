//*******************************************
//Programa del proyecto ESP32 AdminTool
//    29/01/2023
//********************************************


bool settingsReadRelasy();
//---------------------------------------------
// Leer configuraciones de los parámetros WIFI
//--------------------------------------------
bool settingsReadWifi(){
    StaticJsonDocument<500> jsonConfig;
    File file = SPIFFS.open("/SettingsWifi.json", "r");
    if (deserializeJson(jsonConfig, file)) {
        //Si falla la lectura inica valores por defecto
        settingResetWifi();
        log("Error: falló la lectura de la configuración WiFi, tomando valores por defecto");
        return false;
    }else{
    /*----------------------GENERAL--------------------*/
        strlcpy(id,jsonConfig["id"], sizeof(id));
        bootCount = jsonConfig["boot"];
    /*-----------------------CLIENTE-------------------*/

       wifi_staticIP = jsonConfig["wifi_staticIP"];
       strlcpy(wifi_ssid, jsonConfig["wifi_ssid"], sizeof(wifi_ssid));
       strlcpy(wifi_passw, jsonConfig["wifi_passw"], sizeof(wifi_passw));
       strlcpy(wifi_ip_static, jsonConfig["wifi_ip_static"], sizeof(wifi_ip_static));
       strlcpy(wifi_gateway, jsonConfig["wifi_gateway"], sizeof(wifi_gateway));
       strlcpy(wifi_subnet, jsonConfig["wifi_subnet"], sizeof(wifi_subnet));
       strlcpy(wifi_primaryDNS, jsonConfig["wifi_primaryDNS"], sizeof(wifi_primaryDNS));
       strlcpy(wifi_secondaryDNS, jsonConfig["wifi_secondaryDNS"], sizeof(wifi_secondaryDNS));
       /*---------------------------AP------------------------------*/
       ap_accessPoint = jsonConfig["ap_accessPoint"];
       strlcpy(ap_nameap, jsonConfig["ap_nameap"], sizeof(ap_nameap));
       strlcpy(ap_passwordap, jsonConfig["ap_passwordap"], sizeof(ap_passwordap));
       ap_canalap = jsonConfig["ap_canalap"];
       ap_hiddenap = jsonConfig["ap_hiddenap"];
       ap_connetap = jsonConfig["ap_connetap"];
       file.close();
       log("Info_ Lectura configuración WiFi correcta");
       return true;

    }   
}

//---------------------------------------------
// Leer configuraciones de los parámetros MQTT
//--------------------------------------------
bool settingReadMQTT(){
    //Lee la configuración MQTT
    StaticJsonDocument<500> jsonConfig;

    File file = SPIFFS.open("/settingmqtt.json", "r");
    if (deserializeJson(jsonConfig, file)) {
        //Si falla la lectura inica valores por defecto
        settingResetMQTT();
        log("Error: falló la lectura de la configuración MQTT, tomando valores por defecto");
        return false;
    }else{
        //Si lee el archivo
       strlcpy(mqtt_user, jsonConfig["mqtt_user"], sizeof(mqtt_user));
       strlcpy(mqtt_passw, jsonConfig["mqtt_passw"], sizeof(mqtt_passw));
       strlcpy(mqtt_server, jsonConfig["maqtt_server"], sizeof(mqtt_server));
       strlcpy(mqtt_id, jsonConfig["wifi_id"], sizeof(mqtt_id));
       mqtt_time = jsonConfig["mqtt_time"];
       mqtt_port = jsonConfig["mqtt_port"];
       mqtt_enable = jsonConfig["mqtt_enable"];
       file.close();
       log("Info_ Lectura configuración MQTT correcta");
       return true;

    }   
}
//---------------------------------------------
// Leer el estados de los relays
//--------------------------------------------
bool settingsReadRelasy(){
    //Lee 
    StaticJsonDocument<200> jsonConfig;

    File file = SPIFFS.open("/settingrelays.json", "r");
    if (deserializeJson(jsonConfig, file)) {
        //Si falla la lectura inica valores por defecto
        settingResetRelays();
        log("Error: falló la lectura de la lectura de estados deRelay, tomando valores por defecto");
        return false;
    }else{
        //Si lee el archivo
        Relay01_status = jsonConfig["Relay01_status"];
        Relay02_status = jsonConfig["Relay02_status"];
       file.close();
       log("Info_ Lectura de Realys correcta");
       return true;

    }   
}


