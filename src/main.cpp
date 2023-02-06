//*******************************************
//Programa del proyecto ESP32 AdminTool
//    29/01/2023
//********************************************
#include <Arduino.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>

//********************************************
//   Archivos .hpp- para fragmentar el código
//********************************************
#include "settings.hpp"
#include "functions.hpp"
#include "settingsReset.hpp"
#include "settingsRead.hpp"
#include "settingsSave.hpp"
#include "esp32_wifi.hpp"
#include "esp32_mqtt.hpp"

//*************SETUP*******************
void setup() {
  // Bauderate
  Serial.begin(115200);
  // CPU FRECUENCIA
  setCpuFrequencyMhz(240);
  //Inicio del log por serial
  log("\nInfo: Inciando Setup");
  //Configurar los pines
  settingPines();
  //INICIO DEL SPIFSS
  if (!SPIFFS.begin(true))
  {  log(F("Error: Falló la inicialización del SPIFFS"));
      while (true);

  }
   // Lee la configuración de Wifi
  settingsReadRelasy();

  setOnOffSingle(RELAY1, Relay01_status);
  setOnOffSingle(RELAY2, Relay02_status);
  // Lee la configuración de Wifi
  settingsReadWifi();
  // Configuración del wifi
  WiFi.disconnect(true);
  delay(1000);
  //Setup del Wifi
  wifi_setup();
   // Lee la configuración de MQTT
  settingReadMQTT();

}

void loop() {
  yield();  //instrucción para el watchdog
  //----------------------------------------
  //                    WIFI
  //----------------------------------------
  if (wifi_mode == WIFI_STA)
  {
    wifiloop();
  }
  if (wifi_mode == WIFI_AP)
  {
    wifiAPloop();
  }
  //----------------------------------------
  //                    MQTT
  //----------------------------------------
  if ((WiFi.status() == WL_CONNECTED) && (wifi_mode == WIFI_STA))
  {
    if (mqtt_server != 0)
    {
      mqttLoop();
      if (mqttclient.connected())
      {
        if (millis() - lastMsg > mqtt_time)
        {
          lastMsg = millis();
          mqtt_publish();
        }
        
      }
      
    }
    
  }
  
}