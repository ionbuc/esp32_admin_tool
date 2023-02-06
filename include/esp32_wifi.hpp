//*******************************************
//Programa del proyecto ESP32 AdminTool
//    29/01/2023
//********************************************

#include <WiFi.h>
#include <DNSServer.h>
#include <ESPmDNS.h>

const byte DNSSERVER_PORT = 53;
DNSServer dnsServer;
IPAddress apIP(192, 168, 4, 1);
IPAddress netMsk(255, 255, 255, 0);
int wifi_mode = WIFI_STA;
unsigned long previousMillisWIFI = 0;
unsigned long intervalWIFI = 30000;
//Hostname for ESPmDNS. Should work ay least on windows. Try http://adminesp32.local
const char *esp_hostname = id;

 void startAP(){
    log("info: Iniciando modo AP");
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
    WiFi.softAPConfig(apIP, apIP, netMsk);
    WiFi.setHostname(deviceID().c_str());
    WiFi.softAP(ap_nameap, ap_passwordap, ap_canalap, ap_hiddenap, ap_connetap);
    log("Info: WiFi AP " + deviceID() + " - IP " + ipStr(WiFi.softAPIP()));
    dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);
    dnsServer.start(DNSSERVER_PORT, "*", apIP);
    wifi_mode = WIFI_AP;           
}

//---------------------------------
// Start Client, intento de conectarse a la red Wifi
//-----------------------------------
void startClient(){
    if (wifi_staticIP)
    {
        if (!WiFi.config(CharToIP(wifi_ip_static), CharToIP(wifi_gateway), CharToIP(wifi_subnet), CharToIP(wifi_primaryDNS), CharToIP(wifi_secondaryDNS)))
        {
            log("Error: Falló al conectar el modo Estación");
        }
    }
    WiFi.hostname(deviceID());
    WiFi.begin(wifi_ssid, wifi_passw);
    log("Info: Conectando Wifi " + String(wifi_ssid));
    delay(50);
    byte b = 0;
    while (WiFi.status() != WL_CONNECTED && b < 60)
    {
        b++;
        log("Warning: intentando conexión Wifi ...");
        delay(500);
            //para parpadear led EIFI cuando está conectandose al wifi no bloqueante
            //Parpadeo simple del led cada 100 ms
            //BlinkSingle(100, WIFILED);
    } // Fin del While 
    if (WiFi.status() == WL_CONNECTED )
    {   //Wifi conectado a la estación
        log("Info: WiFi conectado (" + String(WiFi.RSSI()) + ") IP " +ipStr(WiFi.localIP()));
        //Parpadeo random del led
        //BlinkSingle(100, WIFILED);
        delay(100);
    }
    else
    {
        log("Error: Wifi no conectado");
        //Parpadeo random del led
        //BlinkSingle(100, WIFILED);
        delay(100);
    }
    
}
//WiFi.mode(WIFI_STA)      -Modo estación: el esp32 se conecta a un access point
//WiFi.mode(WIFI_AP)       -Modo Accesss Point: una estación puede conectarse al ESP32
//WiFi.mode(WIFI_AP_STA)   -Access point y una estación conectada a otro access point

void wifi_setup(){
    WiFi.disconnect();
    // 1) Si está en modo AP
    if (ap_accessPoint)
    {
        startAP();
        log("Info: WiFi Modo AP");
    } 
    // 2) Caso contrario en Modo cliente
    else{
        WiFi.mode(WIFI_STA);
        wifi_mode = WIFI_STA;
        startClient();
        log("Info: WiFi en modo estación");
    }
    // Iniciar hostname broadcast en modo STA o AP
    if (wifi_mode == WIFI_STA || wifi_mode == WIFI_AP)
    {
        if (MDNS.begin(esp_hostname))
        {
            MDNS.addService("http", "tcp", 80);
        }
        
    }
}
//---------------------------------
// Loop modo cliente
//-----------------------------------
void wifiloop(){
    unsigned long currentMillis = millis();
    if (WiFi.status() != WL_CONNECTED && (currentMillis - previousMillisWIFI >= intervalWIFI))
    {   // para parpadear un led cuando esta conectándose al eifi no bloqueante
        // Parpadeo simple del led cada 100 ms
        blinkSingle(100, WIFILED);

        WiFi.disconnect();
        WiFi.reconnect();
        previousMillisWIFI = currentMillis;
    }
    else
    { //parpadeo del led Tiempo On y Tiempo Off
        blinkSingleAsy(100, 500, WIFILED);   
    }  
}
//---------------------------------
// Loop modo AP
//-----------------------------------
void wifiAPloop(){
    //Parpadeo del led con tiempo variable como transferencia de Datos
    blinkRandomSingle(50, 100, WIFILED);
    dnsServer.processNextRequest(); // captive porta NDS re-direct
}