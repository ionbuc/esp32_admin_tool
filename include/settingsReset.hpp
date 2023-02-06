//*******************************************
//Programa del proyecto ESP32 AdminTool
//    29/01/2023
//********************************************

void settingResetWifi(){

    /*----------------------GENERAL--------------------*/
    strlcpy(id, "adminesp32", sizeof(id));
    bootCount = 0;
    /*-----------------------CLIENTE-------------------*/
    bool wifi_staticIP = false;
    strlcpy(wifi_ssid, "Totalplay-5F9E_EXT", sizeof(wifi_ssid));
    strlcpy(wifi_passw, "5F9ED08Cf89CKDuv", sizeof(wifi_passw));
    strlcpy(wifi_ip_static, "192.168.0.150", sizeof(wifi_ip_static));
    strlcpy(wifi_gateway, "192.168.0.1", sizeof(wifi_gateway));
    strlcpy(wifi_subnet, "255.255.255.0", sizeof(wifi_subnet));
    strlcpy(wifi_primaryDNS, "8.8.8.8", sizeof(wifi_primaryDNS));
    strlcpy(wifi_secondaryDNS, "8.8.4.4", sizeof(wifi_secondaryDNS));

    /*-------------------------  AP -------------------*/
    ap_accessPoint = false;
    strlcpy(ap_nameap, deviceID().c_str(), sizeof(ap_nameap));
    strlcpy(ap_passwordap, "adminesp32", sizeof(ap_passwordap));
    ap_canalap = 9;
    ap_hiddenap = false;
    ap_connetap = 4;
}



void settingResetMQTT(){
    //Define configuración por defecto del equipo conexión MQTT
    strlcpy(mqtt_user, "user", sizeof(mqtt_user));
    strlcpy(mqtt_passw, "passwd", sizeof(mqtt_passw));
    strlcpy(mqtt_server, "192.168.100.93", sizeof(mqtt_server));
    strlcpy(mqtt_id, deviceID().c_str(), sizeof(mqtt_id));
    mqtt_time = 60000;
    mqtt_port = 1883;
    mqtt_enable = true;
}
//---------------------------------------------
//Valore por defecto de los relays
//--------------------------------------------
void settingResetRelays(){
    Relay02_status = LOW;
    Relay01_status = LOW;
}