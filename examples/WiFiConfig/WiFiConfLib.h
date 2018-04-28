#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

#ifndef WIFICONFIGLED
#define WIFICONFIGLED     LED_BUILTIN 
#endif

#ifndef WIFICONFIGBUTTON
#define WIFICONFIGBUTTON           D1
#endif

#define EEPROM_SSID_CONF    0
#define EEPROM_PASS_CONF   50
#define EEPROM_STAT_CONF  100
#define EEPROM_SSID       150
#define EEPROM_PASS       200


void setup_conf();
String SSIDread();
String PASSread();
String leer(int addr);
void grabar(int addr, String a);
