#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#define WIFICONFIGLED     LED_BUILTIN 
#define WIFICONFIGBUTTON           D1

//-------------------VARIABLES GLOBALES--------------------------
int contconexion = 0;
unsigned long previousMillis = 0;

char ssid[50];      
char pass[50];

char ssidConf[50];      
char passConf[50];
char confstat[50];

const char *ssidInit = "tutorial";
const char *passInit = "12345678";

String mensaje = "";

//-----------CODIGO HTML PAGINA DE CONFIGURACION---------------
String pagina = "<!DOCTYPE html>"
"<html>"
"<head>"
"<title>Tutorial Eeprom</title>"
"<meta charset='UTF-8'>"
"</head>"
"<body>"
"</form>"
"<form action='guardar_conf' method='get'>"
"<h1>Accés internet</h1>"
"Deixar en blanc per mantenir els valors<br><br>"
"SSID:  "
"<input class='input1' name='ssid' type='text'><br>"
"PASSWORD:  "
"<input class='input1' name='pass' type='password'><br><br>"
"<h1>Servidor configuració</h1>"
"Deixar en blanc per mantenir els valors<br><br>"
"SSIDConf:  "
"<input class='input1' name='ssidConf' type='text'><br>"
"PASSWORDConf:  "
"<input class='input1' name='passConf' type='password'><br><br>"
"<input class='boton' type='submit' value='GUARDAR'/><br><br>"
"</form>"
"<a href='escanear'><button class='boton'>ESCANEAR</button></a><br><br>";

String paginafin = "</body>"
"</html>";

//------------------------SETUP WIFI-----------------------------
void setup_wifi() {
// Conexión WIFI
  WiFi.mode(WIFI_STA); //para que no inicie el SoftAP en el modo normal
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED and contconexion <50) { //Cuenta hasta 50 si no se puede conectar lo cancela
    ++contconexion;
    delay(250);
    Serial.print(".");
    digitalWrite(13, HIGH);
    delay(250);
    digitalWrite(13, LOW);
  }
  if (contconexion <50) {   
      Serial.println("");
      Serial.println("WiFi conectado");
      Serial.println(WiFi.localIP());
      digitalWrite(13, HIGH);  
  }
  else { 
      Serial.println("");
      Serial.println("Error de conexion");
      digitalWrite(13, LOW);
  }
}

//--------------------------------------------------------------
WiFiClient espClient;
ESP8266WebServer server(80);
//--------------------------------------------------------------

//-------------------PAGINA DE CONFIGURACION--------------------
void paginaconf() {
  server.send(200, "text/html", pagina + mensaje + paginafin); 
}

//--------------------MODO_CONFIGURACION------------------------
void modoconf() {
   
  delay(100);
  digitalWrite(WIFICONFIGLED, HIGH);
  delay(100);
  digitalWrite(WIFICONFIGLED, LOW);
  delay(100);
  digitalWrite(WIFICONFIGLED, HIGH);
  delay(100);
  digitalWrite(WIFICONFIGLED, LOW);
  delay(100);
  digitalWrite(WIFICONFIGLED, HIGH);
  delay(100);
  digitalWrite(WIFICONFIGLED, LOW);

  leer(100).toCharArray(confstat, 50);
  Serial.print("confstat=");
  Serial.println(confstat);
  
  if (strcmp(confstat,"SERVER CONF SAVED")==0) {
    leer(0).toCharArray(ssidConf, 50);
    leer(50).toCharArray(passConf, 50);
    WiFi.softAP(ssidConf, passConf);
    Serial.print("ssidConf=");
    Serial.println(ssidConf);
  }
  else {
    WiFi.softAP(ssidInit, passInit);
  }

  IPAddress myIP = WiFi.softAPIP(); 
  Serial.print("IP del acces point: ");
  Serial.println(myIP);
  Serial.println("WebServer iniciado...");

  server.on("/", paginaconf); //esta es la pagina de configuracion

  server.on("/guardar_conf", guardar_conf); //Graba en la eeprom la configuracion

  server.on("/escanear", escanear); //Escanean las redes wifi disponibles
  
  server.begin();

  while (true) {
      server.handleClient();
  }
}

//---------------------GUARDAR CONFIGURACION-------------------------
void guardar_conf() {
  if (server.arg("ssidConf")!="") {
    Serial.println(server.arg("ssidConf"));//Recibimos los valores que envia por GET el formulario web
    grabar(0,server.arg("ssidConf"));
    Serial.println(server.arg("passConf"));
    grabar(50,server.arg("passConf"));
    grabar(100,"SERVER CONF SAVED");
  }
  if (server.arg("ssid")!="") {
    Serial.println(server.arg("ssid"));//Recibimos los valores que envia por GET el formulario web
    grabar(150,server.arg("ssid"));
    Serial.println(server.arg("pass"));
    grabar(200,server.arg("pass"));
  }

  mensaje = "Configuracion Guardada...";
  paginaconf();
}

//----------------Función para grabar en la EEPROM-------------------
void grabar(int addr, String a) {
  int tamano = a.length(); 
  char inchar[50]; 
  a.toCharArray(inchar, tamano+1);
  for (int i = 0; i < tamano; i++) {
    EEPROM.write(addr+i, inchar[i]);
  }
  for (int i = tamano; i < 50; i++) {
    EEPROM.write(addr+i, 255);
  }
  EEPROM.commit();
}

//-----------------Función para leer la EEPROM------------------------
String leer(int addr) {
   byte lectura;
   String strlectura;
   for (int i = addr; i < addr+50; i++) {
      lectura = EEPROM.read(i);
      if (lectura != 255) {
        strlectura += (char)lectura;
      }
   }
   return strlectura;
}

//---------------------------ESCANEAR----------------------------
void escanear() {  
  int n = WiFi.scanNetworks(); //devuelve el número de redes encontradas
  Serial.println("escaneo terminado");
  if (n == 0) { //si no encuentra ninguna red
    Serial.println("no se encontraron redes");
    mensaje = "no se encontraron redes";
  }  
  else
  {
    Serial.print(n);
    Serial.println(" redes encontradas");
    mensaje = "";
    for (int i = 0; i < n; ++i)
    {
      // agrega al STRING "mensaje" la información de las redes encontradas 
      mensaje = (mensaje) + "<p>" + String(i + 1) + ": " + WiFi.SSID(i) + " (" + WiFi.RSSI(i) + ") Ch: " + WiFi.channel(i) + " Enc: " + WiFi.encryptionType(i) + " </p>\r\n";
      //WiFi.encryptionType 5:WEP 2:WPA/PSK 4:WPA2/PSK 7:open network 8:WPA/WPA2/PSK
      delay(10);
    }
    Serial.println(mensaje);
    paginaconf();
  }
}

//------------------------SETUP-----------------------------
void setup() {

  pinMode(WIFICONFIGLED, OUTPUT);  
  
  // Inicia Serial
  Serial.begin(115200);
  Serial.println("");

  EEPROM.begin(512);

  digitalWrite(WIFICONFIGLED, HIGH);
  delay(300);
  digitalWrite(WIFICONFIGLED, LOW);
  delay(300);
  digitalWrite(WIFICONFIGLED, HIGH);
  delay(300);
  digitalWrite(WIFICONFIGLED, LOW);
 
  pinMode(WIFICONFIGBUTTON, INPUT); 
  if (digitalRead(WIFICONFIGBUTTON) == 0) {
    modoconf();
  }

  leer(150).toCharArray(ssid, 50);
  leer(200).toCharArray(pass, 50);

  setup_wifi();
}

//--------------------------LOOP--------------------------------
void loop() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 5000) { //envia la temperatura cada 5 segundos
    previousMillis = currentMillis;
    Serial.println("Funcionado...");
  }
}



