#include "WiFiConfLib.h"

#define WIFICONFIGBUTTON           D7

unsigned long previousMillis = 0;
char ssid[50];      
char pass[50];
int contconexion = 0;



//------------------------SETUP WIFI-----------------------------
void setup_wifi() {
// Conexión WIFI
  WiFi.mode(WIFI_STA); //para que no inicie el SoftAP en el modo normal
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED and contconexion <50) { //Cuenta hasta 50 si no se puede conectar lo cancela
    ++contconexion;
    delay(250);
    Serial.print(".");
    digitalWrite(WIFICONFIGLED, HIGH);
    delay(250);
    digitalWrite(WIFICONFIGLED, LOW);
  }
  if (contconexion <50) {   
      Serial.println("");
      Serial.println("WiFi conectado");
      Serial.println(WiFi.localIP());
      digitalWrite(WIFICONFIGLED, HIGH);  
  }
  else { 
      Serial.println("");
      Serial.println("Error de conexion");
      digitalWrite(WIFICONFIGLED, LOW);
  }
}


//------------------------SETUP-----------------------------
void setup() {
  setup_conf();
  leer(EEPROM_SSID).toCharArray(ssid, 50);
  leer(EEPROM_PASS).toCharArray(pass, 50);
  setup_wifi();
  
  WiFi.mode(WIFI_OFF); //apaga WiFi

}

//--------------------------LOOP--------------------------------
void loop() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 5000) { //envia la temperatura cada 5 segundos
    previousMillis = currentMillis;
    Serial.println("Funcionado...");
  }
}



