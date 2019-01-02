#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#define DBG_OUTPUT_PORT Serial
#include <FS.h>

// Helper functions prototypes
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
void espera(int temps);

