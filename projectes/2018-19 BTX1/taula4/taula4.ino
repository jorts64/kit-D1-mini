//https://lastminuteengineers.com/creating-esp8266-web-server-arduino-ide/
//https://circuits4you.com/2016/12/16/esp8266-web-server-html/

#include <WEMOS_Matrix_LED.h>
MLED mled(5); //set intensity=5
#include <FS.h> // SD
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
const char *ssid = "tecno1234";
const char *password = "robotica";
ESP8266WebServer server(80);

int i = 0;

const char *pagina = "<html>\
<title>matrix</title>\
<meta name='viewport' content='width=device-width, initial-scale=1'>\
</head>\
<body style='background-color:#82e0aa;'>\
<h1 style='font-family:Trebuchet MS;'>MATRIX</h1>\
<p style='font-family:Trebuchet MS;'>Pick an icon to show.</p>\ 
<a href='/dreta'><img src='/img/derecha.JPG'></a>\
<a href='/esquerra'><img src='/img/izquierda.JPG'></a>\
<a href='/amunt'><img src='/img/arriba.JPG'></a>\
<a href='/abaix'><img src='/img/abajo.JPG'></a>\
<a href='/creu'><img src='/img/cruz.JPG'></a>\
</body></html>"; 




//FLETXA DRETA
const uint64_t img1[] = {
  0x0010307fff7f3010,
  0xffefcf800080cfef
};
const int IMAGES_LEN = sizeof(img1)/8;
//FLETXA ESQUERRA
const uint64_t img2[] = {
  0x00080cfefffe0c08,
  0xfff7f3010001f3f7
};

//FLETXA CAP A DALT
const uint64_t img3[] = {
  0x1c1c1c1c7f3e1c08,
  0xe3e3e3e380c1e3f7
};
//FLETXA CAP A BAIX
const uint64_t img4[] = {
  0x081c3e7f1c1c1c1c,
  0xf7e3c180e3e3e3e3
};

//CREU
const uint64_t img5[] = {
  0x42e77e3c3c7ee742,
  0xbd1881c3c38118bd
};
//off
const uint64_t img6[] = {
  0x0000000000000000
 
};


void displayImage(uint64_t image) {
for (int i = 0; i < 8; i++) {
byte row = (image >> i * 8) & 0xFF;
for (int j = 0; j < 8; j++) {
mled.dot(j, 7-i, bitRead(row, j));
}
}
mled.display();
} 

void esquerre(){
  displayImage(img2[i]);
if (++i >= IMAGES_LEN ) {
i = 0;
  }
}
 
void dreta(){
  displayImage(img1[i]);
if (++i >= IMAGES_LEN ) {
i = 0;
  }
}
 
void amunt(){
  displayImage(img3[i]);
if (++i >= IMAGES_LEN ) {
i = 0;
  }
}
 
void abaix(){
  displayImage(img4[i]);
if (++i >= IMAGES_LEN ) {
i = 0;
  }
}

  void creu(){
  displayImage(img5[i]);
if (++i >= IMAGES_LEN ) {
i = 0;
  }
  }
    void off(){
  displayImage(img6[i]);
if (++i >= IMAGES_LEN ) {
i = 0;
  }
    }
 
 
void setup() {
WiFi.mode(WIFI_AP);
Serial.begin(9600);
WiFi.softAP(ssid, password);
SPIFFS.begin();
server.on ( "/", handleRoot);
server.serveStatic("/img", SPIFFS, "/img"); //  imatges dir
  server.on("/esquerra",esquerre);
  server.on("/dreta",dreta);
  server.on("/amunt",amunt);
  server.on("/abaix",abaix);
  server.on("/creu",creu);
  server.on("/off",off);
  server.begin();

}

 void handleRoot() {

  server.send (200, "text/html", pagina);
  
}


void loop() {
  server.handleClient();
  delay(10);
  }

