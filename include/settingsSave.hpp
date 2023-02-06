
//---------------------------------------------
// Guardarlos estados de los relays
//--------------------------------------------
bool settingsSaveRelays(){
    //Guarda configuración de los
    StaticJsonDocument<200> jsonConfig;  //Se crea un archivo con nombre jsonConfig

    File file = SPIFFS.open("/settingrelays.json", "w+");
    if (file) {
        jsonConfig["Relay01_status"] = Relay01_status;
        jsonConfig["Relay02_status"] = Relay02_status;
        serializeJsonPretty(jsonConfig, file);
        file.close();
        log(F("Info: estado de los relays guardado"));
        serializeJsonPretty(jsonConfig, Serial);
        return true;
    }else{
             
       log("Error: Falló el guardado del estado de los Realy");
       return false;

    }   
}