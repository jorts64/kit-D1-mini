/***************************************************************************
Camèra tèrmica amb AMG8833, D1 mini, TFT1.4, RTC, OLED i keypad
interpolació
OTA / FSmanager / foto / canvi maxtemp i mintemp / cataleg
***************************************************************************/

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FS.h>
File f;

#define DBG_OUTPUT_PORT Serial

const char* ssid = "jortsnet";
const char* password = "9periodico";
const char* host = "esp8266fs";
// tria el tipus de connexió. Client WIFI_STA, Access Point WIFI_AP
int MODE_WIFI=WIFI_STA;

ESP8266WebServer server(80);
File fsUploadFile;


#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>

#include <Wire.h>
#include <Adafruit_AMG88xx.h>

#define TFT_RST -1 //for TFT I2C Connector Shield V1.0.0 and TFT 1.4 Shield V1.0.0
#define TFT_CS D4  //for TFT I2C Connector Shield V1.0.0 and TFT 1.4 Shield V1.0.0
#define TFT_DC D3  //for TFT I2C Connector Shield V1.0.0 and TFT 1.4 Shield V1.0.0

// #define TFT_RST -1   //for TFT I2C Connector Shield (V1.1.0 or later)
// #define TFT_CS D0    //for TFT I2C Connector Shield (V1.1.0 or later)
// #define TFT_DC D8    //for TFT I2C Connector Shield (V1.1.0 or later)

#include <SFE_MicroOLED.h>  // Include the SFE_MicroOLED library
#define PIN_RESET 255  // Connect RST to pin 9
#define DC_JUMPER 0
MicroOLED oled(PIN_RESET, DC_JUMPER);    // I2C declaration 

#include "RTClib.h"
RTC_DS1307 RTC;
DateTime now;

//Comment this out to remove the text overlay
//#define SHOW_TEMP_TEXT

//low range of the sensor (this will be blue on the screen)
#define MINTEMP 20

//high range of the sensor (this will be red on the screen)
#define MAXTEMP 28

float mintemp = MINTEMP;
float maxtemp = MAXTEMP;
float minT,maxT;

//the colors we will be using
const uint16_t camColors[] = {0x480F,
0x400F,0x400F,0x400F,0x4010,0x3810,0x3810,0x3810,0x3810,0x3010,0x3010,
0x3010,0x2810,0x2810,0x2810,0x2810,0x2010,0x2010,0x2010,0x1810,0x1810,
0x1811,0x1811,0x1011,0x1011,0x1011,0x0811,0x0811,0x0811,0x0011,0x0011,
0x0011,0x0011,0x0011,0x0031,0x0031,0x0051,0x0072,0x0072,0x0092,0x00B2,
0x00B2,0x00D2,0x00F2,0x00F2,0x0112,0x0132,0x0152,0x0152,0x0172,0x0192,
0x0192,0x01B2,0x01D2,0x01F3,0x01F3,0x0213,0x0233,0x0253,0x0253,0x0273,
0x0293,0x02B3,0x02D3,0x02D3,0x02F3,0x0313,0x0333,0x0333,0x0353,0x0373,
0x0394,0x03B4,0x03D4,0x03D4,0x03F4,0x0414,0x0434,0x0454,0x0474,0x0474,
0x0494,0x04B4,0x04D4,0x04F4,0x0514,0x0534,0x0534,0x0554,0x0554,0x0574,
0x0574,0x0573,0x0573,0x0573,0x0572,0x0572,0x0572,0x0571,0x0591,0x0591,
0x0590,0x0590,0x058F,0x058F,0x058F,0x058E,0x05AE,0x05AE,0x05AD,0x05AD,
0x05AD,0x05AC,0x05AC,0x05AB,0x05CB,0x05CB,0x05CA,0x05CA,0x05CA,0x05C9,
0x05C9,0x05C8,0x05E8,0x05E8,0x05E7,0x05E7,0x05E6,0x05E6,0x05E6,0x05E5,
0x05E5,0x0604,0x0604,0x0604,0x0603,0x0603,0x0602,0x0602,0x0601,0x0621,
0x0621,0x0620,0x0620,0x0620,0x0620,0x0E20,0x0E20,0x0E40,0x1640,0x1640,
0x1E40,0x1E40,0x2640,0x2640,0x2E40,0x2E60,0x3660,0x3660,0x3E60,0x3E60,
0x3E60,0x4660,0x4660,0x4E60,0x4E80,0x5680,0x5680,0x5E80,0x5E80,0x6680,
0x6680,0x6E80,0x6EA0,0x76A0,0x76A0,0x7EA0,0x7EA0,0x86A0,0x86A0,0x8EA0,
0x8EC0,0x96C0,0x96C0,0x9EC0,0x9EC0,0xA6C0,0xAEC0,0xAEC0,0xB6E0,0xB6E0,
0xBEE0,0xBEE0,0xC6E0,0xC6E0,0xCEE0,0xCEE0,0xD6E0,0xD700,0xDF00,0xDEE0,
0xDEC0,0xDEA0,0xDE80,0xDE80,0xE660,0xE640,0xE620,0xE600,0xE5E0,0xE5C0,
0xE5A0,0xE580,0xE560,0xE540,0xE520,0xE500,0xE4E0,0xE4C0,0xE4A0,0xE480,
0xE460,0xEC40,0xEC20,0xEC00,0xEBE0,0xEBC0,0xEBA0,0xEB80,0xEB60,0xEB40,
0xEB20,0xEB00,0xEAE0,0xEAC0,0xEAA0,0xEA80,0xEA60,0xEA40,0xF220,0xF200,
0xF1E0,0xF1C0,0xF1A0,0xF180,0xF160,0xF140,0xF100,0xF0E0,0xF0C0,0xF0A0,
0xF080,0xF060,0xF040,0xF020,0xF800,};

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

Adafruit_AMG88xx amg;
unsigned long delayTime;

#define AMG_COLS 8
#define AMG_ROWS 8
float pixels[AMG_COLS * AMG_ROWS];

#define INTERPOLATED_COLS 24
#define INTERPOLATED_ROWS 24

float dest_2d[INTERPOLATED_ROWS * INTERPOLATED_COLS];

// Interpolation functions
float get_point(float *p, uint8_t rows, uint8_t cols, int8_t x, int8_t y);
void set_point(float *p, uint8_t rows, uint8_t cols, int8_t x, int8_t y, float f);
void get_adjacents_1d(float *src, float *dest, uint8_t rows, uint8_t cols, int8_t x, int8_t y);
void get_adjacents_2d(float *src, float *dest, uint8_t rows, uint8_t cols, int8_t x, int8_t y);
float cubicInterpolate(float p[], float x);
float bicubicInterpolate(float p[], float x, float y);
void interpolate_image(float *src, uint8_t src_rows, uint8_t src_cols, 
                       float *dest, uint8_t dest_rows, uint8_t dest_cols);
// WiFi Helper functions prototypes
void OkRetorn();
void printDirectory();
void handleFileCreate();
void handleFileDelete();
void handleFileUpload();
String formatBytes(size_t bytes);
String getContentType(String filename);
bool handleFileRead(String path);
void handleFileEdit();
void handleFileSave();
void initHelper();
void initWifi();
void pageHead();
// Other functions
String getLine();
String getValue(String data, char separator, int index);
int readbutton();
int tecla;
void OTAwait();
void muestraFoto(String fn, int npos, int ntot);
        
void setup() {
  pinMode(D0, INPUT);
  delay(500);
  Serial.begin(115200);  
  SPIFFS.begin();
  tft.initR(INITR_144GREENTAB);   // initialize a ST7735S chip, black tab
  tft.setRotation(3);
  tft.fillScreen(ST7735_BLACK);
  amg.begin();
  oled.begin();    
  oled.clear(ALL); 
  oled.display();  
  delay(1000);     
  oled.clear(PAGE); 
  RTC.begin();
//  RTC.adjust(DateTime(__DATE__, __TIME__));  //uncomment 1st upload to adjust time
}

void loop() {
  tecla = readbutton();
  unsigned long ara;

  amg.readPixels(pixels);

  minT=pixels[0];
  maxT=pixels[0];
  for(int i=1; i<AMG_COLS * AMG_ROWS; i++){
    minT=min(minT,pixels[i]);
    maxT=max(maxT,pixels[i]);
  }

  now = RTC.now(); 
  oledData();

  pintaFoto();

  if (digitalRead(D0) == LOW) {             // button on D0 for developing proposes
    oledOTA();
    OTAwait();
  }
  if (tecla == 5) {                         // LEFT
    ara=millis();
    while ((readbutton()==5)&&((millis()-ara)<=10000)) delay(1);
    if ((millis()-ara)>=10000)
      FMWifiAP(); 
    else {
      mintemp--;
    }
  }
  if (tecla == 2) {                         // RIGHT
    ara=millis();
    while ((readbutton()==2)&&((millis()-ara)<=10000)) delay(1);
    if ((millis()-ara)>=10000)
      FMWifi();
    else {
      mintemp++;
      if (maxtemp-mintemp < 5)
        maxtemp = mintemp + 5;
    }
  }
  if (tecla == 4) {                         // UP
    ara=millis();
    while ((readbutton()==4)&&((millis()-ara)<=5000)) delay(1);
    if ((millis()-ara)>=5000)
      cataleg();
    else {
    maxtemp++;
    }
  }
  if (tecla == 3) {                         // DOWN
    ara=millis();
    while ((readbutton()==3)&&((millis()-ara)<=10000)) delay(1);
    if ((millis()-ara)>=10000){
      oledOTA();
      OTAwait();
      }
    else {
      maxtemp--;
      if (maxtemp-mintemp < 5)
        mintemp = maxtemp - 5;
    }
  }
  if (tecla == 1) {                         // SHOT
    takeFoto();
    delay (2000);
  }
  delay(1);
}


void cataleg(){
  String fileName[100];
  String nom;
  int n=0;
  int pos,i; 
  oled.clear(PAGE);
  oled.setFontType(0);
  oled.setCursor(0,0);
  oled.println("Cercant");
  oled.println("fotos");
  oled.display(); 
  delay(1000);
  Dir dir = SPIFFS.openDir("/");
  while (dir.next()) {
    nom = dir.fileName();
    oled.clear(PAGE);
    oled.setFontType(0);
    oled.setCursor(0,0);
    oled.println(nom);
    if ((nom.startsWith("/foto"))&&(n<100)){
      fileName[n] = nom;
      n++;
    }
    oled.display(); 
    delay(10);
  }
  oled.clear(PAGE);
  oled.setFontType(0);
  oled.setCursor(0,0);
  oled.println("Trobades");
  oled.print(n, DEC);
  oled.println(" fotos");
  oled.display(); 
  delay(1000);
  pos=n-1;
  muestraFoto(fileName[pos],pos,n);
  tecla = readbutton();
  while (tecla!=4) {
    if (tecla==2) {
      pos++;
      if (pos==n) pos=0; 
      muestraFoto(fileName[pos],pos,n);
      delay(300);
    }
    if (tecla==5) {
      if(pos==0)
        pos=n-1;
      else 
        pos--; 
      muestraFoto(fileName[pos],pos,n);
      delay(300);
    }
    if (tecla==3) {
      oled.clear(PAGE);
      oled.setFontType(0);
      oled.setCursor(0,0);
      oled.println("Borrar");
      oled.print(fileName[pos]);
      oled.println(" ?");
      oled.println("left NO");
      oled.println("right SI");
      oled.display(); 
      delay(1000);
      while ((tecla!=2)&&(tecla!=5)){
        tecla = readbutton();
        delay(1);        
      }
      if (tecla==2) {
        SPIFFS.remove(fileName[pos]);
        n--;
        for (i=pos;i<n;i++) {
          fileName[i]=fileName[i+1];
        }
        if (pos==n) pos=0;
        oled.clear(PAGE);
        oled.setFontType(0);
        oled.setCursor(0,0);
        oled.println("Foto");
        oled.println("Borrada");
        oled.display(); 
        delay(1000);
        muestraFoto(fileName[pos],pos,n);
      }
      else {
        oled.clear(PAGE);
        oled.setFontType(0);
        oled.setCursor(0,0);
        oled.println("Borrado");
        oled.println("Cancelado");
        oled.display(); 
        delay(1000);
        muestraFoto(fileName[pos],pos,n);
      }
      tecla=0;
    }
    tecla = readbutton();
    delay(10);
  }
  tecla=0;
}

void muestraFoto(String fn, int npos, int ntot){
  String txt;
  float sa[8]; 
  int r,t;
  delay(1);
  f = SPIFFS.open(fn,"r");
  oled.clear(PAGE);
  oled.setFontType(0);
  oled.setCursor(0,0);
  oled.print("< > ");
  oled.print(npos+1, DEC);
  oled.print("/");
  oled.println(ntot);
  txt=getLine();
  oled.println(txt);
  txt=getLine();
  oled.println(txt);
  txt=getLine();
//  oled.println(txt);
  txt=getLine(); // map
  for (r=0;txt.charAt(r)!='-';r++);
  mintemp=txt.substring(0,r-1).toFloat();
  maxtemp=txt.substring(r+1).toFloat();
  oled.println(txt);
  txt=getLine();
  oled.println(txt);
  txt=getLine();
  oled.println(txt);
  oled.display(); 
  for (int i=0;i<8;i++){
    txt=getLine();
    r=0; t=0;
    for (int k=0; k <txt.length(); k++) { 
      if(txt.charAt(k) == ',')  { 
        sa[t] = txt.substring(r, k).toFloat(); 
        r=(k+1); 
        t++; 
      }
    }
    for (int j=0;j<8;j++) {
        pixels[i*8+j]=sa[j];
    }
  }
  f.close();    
  delay(1);
  pintaFoto();
}

String getLine() {
  String S = "" ;
  char c = f.read(); 
  while ( c != '\n')      
       {     
             S = S + c ;
             c = f.read();
       }
  return(S) ;
}

void pintaFoto(){
  interpolate_image(pixels, AMG_ROWS, AMG_COLS, dest_2d, INTERPOLATED_ROWS, INTERPOLATED_COLS);
  delay(1);
  uint16_t boxsize = min(tft.width() / INTERPOLATED_COLS, tft.height() / INTERPOLATED_COLS);
  drawpixels(dest_2d, INTERPOLATED_ROWS, INTERPOLATED_COLS, boxsize, boxsize);  
  delay(1);
}

void oledData(){
  delay(1);
  oled.clear(PAGE);
  oled.setFontType(0);
  oled.setCursor(0,0);
  oled.print(now.day(), DEC);
  oled.print("/");
  oled.print(now.month(), DEC);
  oled.print("/");
  oled.println(now.year()%2000, DEC);
  oled.print(now.hour(), DEC);
  oled.print(":");
  oled.print(now.minute(), DEC);
  oled.print(":");
  oled.println(now.second(), DEC);
  delay(1);
  oled.print(mintemp, 1);
  oled.print("-");
  oled.println(maxtemp, 1);
  oled.print("Tmin:");
  oled.println(minT, 1);
  oled.print("Tmax:");
  oled.println(maxT, 1);
  delay(1);
  oled.display();
  delay(1); 
}

void takeFoto(){
  String fname = "/foto";
  char temp[100];
  snprintf(temp, 100, "%d",now.year()%2000); 
  fname += temp;
  snprintf(temp, 100, "%d",now.month()); 
  fname += temp;
  snprintf(temp, 100, "%d",now.day()); 
  fname += temp;
  snprintf(temp, 100, "%d",now.hour()); 
  fname += temp;
  snprintf(temp, 100, "%d",now.minute()); 
  fname += temp;
  snprintf(temp, 100, "%d",now.second()); 
  fname += temp;
  fname += ".dat";
  f = SPIFFS.open(fname,"w");
  f.print(now.day(), DEC);
  f.print("/");
  f.print(now.month(), DEC);
  f.print("/");
  f.println(now.year()%2000, DEC);
  f.print(now.hour(), DEC);
  f.print(":");
  f.print(now.minute(), DEC);
  f.print(":");
  f.println(now.second(), DEC);
  f.print("T(Th) = ");
  f.println(amg.readThermistor());
  f.print(mintemp, 1);
  f.print("-");
  f.println(maxtemp, 1);
  f.print("Tmin:");
  f.println(minT, 1);
  f.print("Tmax:");
  f.println(maxT, 1);
  for(int i=1; i<=AMG_COLS * AMG_ROWS; i++){
    f.print(pixels[i-1]);
    f.print(", ");
    if( i%8 == 0 ) f.println();
  }
  f.println();
  f.close();
  oled.clear(PAGE);
  oled.setFontType(0);
  oled.setCursor(0,0);
  oled.println("Imatge");
  oled.println("desada");
  oled.print(fname);
  oled.display();  
}

void FMWifi(){
  oled.clear(PAGE);
  oled.setFontType(0);
  oled.setCursor(0,0);
  oled.println("Gestor de");
  oled.println("fitxers");
  oled.println("WiFi");
  oled.print("Connectant");
  oled.println("a xarxa");
  oled.display();
  initHelper(); //inclou connexió Wifi
  server.begin();
  DBG_OUTPUT_PORT.println("HTTP server started");
  oled.clear(PAGE);
  oled.setFontType(0);
  oled.setCursor(0,0);
  oled.println("Gestor de");
  oled.println("fitxers");
  oled.println("WiFi a ");
  oled.print("http://");
  oled.print(WiFi.localIP());
  oled.println("/dir");
  oled.display();
  while(true) {
    server.handleClient();
    delay(1);
  }    
}

void FMWifiAP(){
  MODE_WIFI=WIFI_AP;
  oled.clear(PAGE);
  oled.setFontType(0);
  oled.setCursor(0,0);
  oled.println("Gestor de");
  oled.println("fitxers");
  oled.println("WiFi");
  oled.print("Creant");
  oled.println("xarxa");
  oled.display();
  initHelper(); //inclou connexió Wifi
  server.begin();
  DBG_OUTPUT_PORT.println("HTTP server started");
  oled.clear(PAGE);
  oled.setFontType(0);
  oled.setCursor(0,0);
  oled.println("Gestor de");
  oled.println("fitxers");
  oled.println("WiFi a ");
  oled.println("http://192.168.4.1/dir");
  oled.display();
  while(true) {
    server.handleClient();
    delay(1);
  }    
}

void drawpixels(float *p, uint8_t rows, uint8_t cols, uint8_t boxWidth, uint8_t boxHeight) {
  int colorTemp;
  for (int y=0; y<rows; y++) {
    for (int x=0; x<cols; x++) {
      float val = get_point(p, rows, cols, x, y);
      if(val >= maxtemp) colorTemp = maxtemp;
      else if(val <= mintemp) colorTemp = mintemp;
      else colorTemp = val;
      uint8_t colorIndex = map(colorTemp, mintemp, maxtemp, 0, 255);
      colorIndex = constrain(colorIndex, 0, 255);
      //draw the pixels!
      uint16_t color;
      color = val * 2;
      tft.fillRect(boxWidth * x, boxHeight * y, boxWidth, boxHeight, camColors[colorIndex]);
    } 
  }
}

int readbutton() {
  int button = analogRead(A0);
  if (button > 900) return (0);
  if (button > 600) return (1);
  if (button > 450) return (2);
  if (button > 250) return (3);
  if (button > 100) return (4);
  return (5);      
}

void oledOTA(){
  oled.clear(PAGE);
  oled.setFontType(0);
  oled.setCursor(0,0);
  oled.println("Esperant");
  oled.println("firmware");
  oled.println("OTA");
  oled.display();  
}

void OTAwait(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) delay(1);

  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  // ArduinoOTA.setHostname("myesp8266");

  // No authentication by default
  // ArduinoOTA.setPassword("admin");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_SPIFFS
      type = "filesystem";
    }

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  while(true) {
      ArduinoOTA.handle();
      delay(1);
  }

}

//----------------------------------------- Helper functions ---------------------------

void pageHead(){
  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
  server.send(200, "text/html", "");
  server.sendContent("<!DOCTYPE html><html><head><title>Gesti&oacute; de fitxersr</title><meta charset='UTF-8'><meta name='viewport' content='width=device-width'/></head><body>");  
}

void initWifi(){
  if (MODE_WIFI==WIFI_STA) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    DBG_OUTPUT_PORT.printf("Connecting to %s\n", ssid);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      DBG_OUTPUT_PORT.print(".");
    }
    DBG_OUTPUT_PORT.println("");
    DBG_OUTPUT_PORT.print("Connected! IP address: ");
    DBG_OUTPUT_PORT.println(WiFi.localIP());

    DBG_OUTPUT_PORT.print("Open http://");
    DBG_OUTPUT_PORT.print(WiFi.localIP());
    DBG_OUTPUT_PORT.println("/dir to see the file browser");
  }
  else {
    WiFi.mode(WIFI_AP);
    WiFi.softAP("IRCamera", "robotica");
    DBG_OUTPUT_PORT.print("Open http://192.168.4.1/dir to see the file browser");
  }
}

void initHelper(){
  DBG_OUTPUT_PORT.print("\n");
  DBG_OUTPUT_PORT.setDebugOutput(true);
    Dir dir = SPIFFS.openDir("/");
    while (dir.next()) {
      String fileName = dir.fileName();
      size_t fileSize = dir.fileSize();
      DBG_OUTPUT_PORT.printf("FS File: %s, size: %s\n", fileName.c_str(), formatBytes(fileSize).c_str());
      DBG_OUTPUT_PORT.printf("\n");
  }

  initWifi();

  //SERVER INIT
  server.on("/dir", HTTP_GET, printDirectory);
  server.on("/create", HTTP_GET, handleFileCreate);
  server.on("/delete", HTTP_GET, handleFileDelete);
  //first callback is called after the request has ended with all parsed arguments
  //second callback handles file uploads at that location
  server.on("/upload", HTTP_POST, []() {
      OkRetorn();
  }, handleFileUpload);
  server.on("/edit", HTTP_GET, handleFileEdit);
  server.on("/save", HTTP_POST, handleFileSave);
  //called when the url is not defined here
  //use it to load content from SPIFFS
  server.onNotFound([]() {
    if (!handleFileRead(server.uri())) {
      server.send(404, "text/plain", "FileNotFound");
    }
  });
  
}

void OkRetorn() {
  pageHead();
  server.sendContent("Operaci&oacute; realitzada amb &egrave;xit<br/><a href='/dir'>Tornar a gesti&oacute; de fitxers</a></body></html>");
}

void printDirectory(){
  Dir dir = SPIFFS.openDir("/");
  pageHead();
  server.sendContent("<h1>Gesti&oacute; de fitxers SD virtual</h1>");
  while (dir.next()) {
    String fileName = dir.fileName();
    size_t fileSize = dir.fileSize();
    DBG_OUTPUT_PORT.printf("FS File: %s, size: %s\n", fileName.c_str(), formatBytes(fileSize).c_str());
    String output;
    output += "<a href='/";
    output += fileName.substring(1);
    output +="'>";
    output += fileName.substring(1);
    output +="</a> ";
    output += formatBytes(fileSize).c_str();
    output += "     <a href='";
    output += fileName;
    output +="?download=1' style='text-decoration: none;'> &#9921; </a>&nbsp;&nbsp;";
    output += "     <a href='/edit?fe=";
    output += fileName;
    output +="' style='text-decoration: none;'> &#9997; </a>&nbsp;&nbsp;";
    output += "     <a href='/delete?killfitxer=";
    output += fileName;
    output +="' style='text-decoration: none;'> &#10006; </a><br/>";
    server.sendContent(output);
    DBG_OUTPUT_PORT.println(output);

  }
  
  server.sendContent("<br/><form action='/create'>Fitxer nou: <input type='text' name='noufitxer' value=''>  <input type='submit' value='Crea'></form>");
  server.sendContent("<br/><form method='post' enctype='multipart/form-data' action='/upload'>Fitxer a enviar: <input type='file' name='myFile'><input type='submit' value='Envia'></form>");
  server.sendContent("</body></html>");
}

void handleFileCreate() {
  if (server.args() == 0) {
    return server.send(500, "text/plain", "BAD ARGS");
  }
  String path = "/" + server.arg("noufitxer");
  DBG_OUTPUT_PORT.println("handleFileCreate: " + path);
  if (path == "/") {
    return server.send(500, "text/plain", "BAD PATH");
  }
  if (SPIFFS.exists(path)) {
    return server.send(500, "text/plain", "FILE EXISTS");
  }
  File file = SPIFFS.open(path, "w");
  if (file) {
    file.close();
  } else {
    return server.send(500, "text/plain", "CREATE FAILED");
  }
  OkRetorn();
  path = String();
}

void handleFileDelete() {
  if (server.args() == 0) {
    return server.send(500, "text/plain", "BAD ARGS");
  }
  String path = server.arg("killfitxer");
  DBG_OUTPUT_PORT.println("handleFileDelete: " + path);
  if (path == "/") {
    return server.send(500, "text/plain", "BAD PATH");
  }
  if (!SPIFFS.exists(path)) {
    return server.send(404, "text/plain", "FileNotFound");
  }
  SPIFFS.remove(path);
  OkRetorn();
  path = String();
}

void handleFileUpload() {
  if (server.uri() != "/upload") {
    return;
  }
  HTTPUpload& upload = server.upload();
  if (upload.status == UPLOAD_FILE_START) {
    String filename = upload.filename;
    if (!filename.startsWith("/")) {
      filename = "/" + filename;
    }
    DBG_OUTPUT_PORT.print("handleFileUpload Name: "); DBG_OUTPUT_PORT.println(filename);
    fsUploadFile = SPIFFS.open(filename, "w");
    filename = String();
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    //DBG_OUTPUT_PORT.print("handleFileUpload Data: "); DBG_OUTPUT_PORT.println(upload.currentSize);
    if (fsUploadFile) {
      fsUploadFile.write(upload.buf, upload.currentSize);
    }
  } else if (upload.status == UPLOAD_FILE_END) {
    if (fsUploadFile) {
      fsUploadFile.close();
    }
    DBG_OUTPUT_PORT.print("handleFileUpload Size: "); DBG_OUTPUT_PORT.println(upload.totalSize);
  }
}

String formatBytes(size_t bytes) {
  if (bytes < 1024) {
    return String(bytes) + "B";
  } else if (bytes < (1024 * 1024)) {
    return String(bytes / 1024.0) + "KB";
  } else if (bytes < (1024 * 1024 * 1024)) {
    return String(bytes / 1024.0 / 1024.0) + "MB";
  } else {
    return String(bytes / 1024.0 / 1024.0 / 1024.0) + "GB";
  }
}

String getContentType(String filename) {
  if (server.hasArg("download")) {
    return "application/octet-stream";
  } else if (filename.endsWith(".htm")) {
    return "text/html";
  } else if (filename.endsWith(".html")) {
    return "text/html";
  } else if (filename.endsWith(".css")) {
    return "text/css";
  } else if (filename.endsWith(".js")) {
    return "application/javascript";
  } else if (filename.endsWith(".png")) {
    return "image/png";
  } else if (filename.endsWith(".gif")) {
    return "image/gif";
  } else if (filename.endsWith(".jpg")) {
    return "image/jpeg";
  } else if (filename.endsWith(".ico")) {
    return "image/x-icon";
  } else if (filename.endsWith(".xml")) {
    return "text/xml";
  } else if (filename.endsWith(".pdf")) {
    return "application/x-pdf";
  } else if (filename.endsWith(".zip")) {
    return "application/x-zip";
  } else if (filename.endsWith(".gz")) {
    return "application/x-gzip";
  }
  return "text/plain";
}

bool handleFileRead(String path) {
  DBG_OUTPUT_PORT.println("handleFileRead: " + path);
  if (path.endsWith("/")) {
    path += "index.htm";
  }
  String contentType = getContentType(path);
  String pathWithGz = path + ".gz";
  if (SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)) {
    if (SPIFFS.exists(pathWithGz)) {
      path += ".gz";
    }
    File file = SPIFFS.open(path, "r");
    server.streamFile(file, contentType);
    file.close();
    return true;
  }
  return false;
}

void handleFileEdit() {
  if (server.args() == 0) {
    return server.send(500, "text/plain", "BAD ARGS");
  }
  String path = server.arg("fe");
  DBG_OUTPUT_PORT.println("handleFileEdit: " + path);
  if (path == "/") {
    return server.send(500, "text/plain", "BAD PATH");
  }
  if (!SPIFFS.exists(path)) {
    DBG_OUTPUT_PORT.print("handleFileEdit Name: "); DBG_OUTPUT_PORT.print(path);DBG_OUTPUT_PORT.println(" FileNotFound"); 
    return server.send(404, "text/plain", "FileNotFound");
  }
  pageHead();
  server.sendContent("<form action='/save' method='POST'>Fitxer: <input type='text' name='nomfitxer' value='");
  server.sendContent(path);
  server.sendContent("' readonly><br/><textarea name='cos' rows='30' cols='40' wrap='off'>");
 
  File file = SPIFFS.open(path,"r");
  char buffer[2];
  buffer[1] = 0;
//  server.streamFile(file, "text/plain");
  while (file.readBytes(buffer, 1)!=0 ) {
    server.sendContent(buffer); 
  }
  file.close();
  server.sendContent("</textarea><br><input type='submit' value='Desa'></form></body></html>");
  
  path = String();
}

void handleFileSave() {
  String path = server.arg("nomfitxer");
  String text = server.arg("cos");
  DBG_OUTPUT_PORT.println("handleFileSave: " + path);
  DBG_OUTPUT_PORT.println("text: " + text);
  File file = SPIFFS.open(path,"w");
  if (!file) {
    DBG_OUTPUT_PORT.println("file open failed");
  }
  file.print(text);
  file.close();
  OkRetorn();
  path = String();
  text = String();
}


