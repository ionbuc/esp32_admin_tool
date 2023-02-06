//*******************************************
//Programa del proyecto ESP32 AdminTool
//    29/01/2023
//********************************************


//**********************
// DEFINICIONES
//**********************

#define RELAY1  27   // GPIO27 para salida de Relay 1
#define RELAY2  26   // GPIO26 para salida de Relay 2
#define WIFILED 12   // GPIO12 led indicador de Wifi
#define MQTTLED 13   // GPIO13 led indicador de MQTT

//**********************
// Versión del Hardware
//*********************
#define HW "ADMINESP32 v1 000000"   // Versión del hardware

//**********************
// Zona Wifi
//*********************
bool wifi_staticIP;         //Uso de IP estática
char wifi_ssid[30];         //Red Wifi
char wifi_passw[30];        //Contraseña de red Wifi
char wifi_ip_static[15];    //ip estático
char wifi_gateway[15];      //Gateway
char wifi_subnet[15];       //Subred
char wifi_primaryDNS[15];   //DNS primario
char wifi_secondaryDNS[15]; //DNS secundario
//------------------------------
//Configuraciones generales
//------------------------------
char id[30];                //ID del dispositivo
int  bootCount;             //Número de reinicios
//**********************
// Zona AP
//*********************
bool ap_accessPoint;        //Uso del AP
char ap_nameap[31];         //SSID AP
char ap_passwordap[63];     //Password AP
int  ap_canalap;            //Canal de AP
int  ap_hiddenap;           //Es visible o no el AP (0 - visible, 1 - oculto)
int  ap_connetap;           // Número de conexiones en el AP
//**********************
// Zona configuración MQTT
//*********************
bool mqtt_enable;           //Habilitar MQTT Broker
char mqtt_user[30];         //Usuario MQTT Broker
char mqtt_id[30];           //id MQTT Broker
char mqtt_passw[30];         //Password MQTT Broker
char mqtt_server[30];         //Servidor del  MQTT Broker
int mqtt_port;             // Puerto servidor MQTT Broker
int mqtt_time;             // Tiempo de envio por MQTT


//**********************
// Zona Otras
//*********************
uint8_t ip[4];
float TempCPU;
//**********************
// Zona Relays
//*********************
bool Relay01_status, Relay02_status; //estados de los leds o realys

