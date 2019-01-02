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

const char* ssid = "nom de la xarxa";
const char* password = "contrasenya";
const char* host = "esp8266fs";
// tria el tipus de connexió. Client WIFI_STA, Access Point WIFI_AP
#define MODE_WIFI WIFI_STA

ESP8266WebServer server(80);
File fsUploadFile;

void espera(int temps) {
  unsigned long ara = millis();
  unsigned long seguent = ara + temps;
  delay(1); //refresh watchdog
  while (millis()<seguent){
      server.handleClient();
  }
}

void pageHead(){
  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
  server.send(200, "text/html", "");
  server.sendContent("<!DOCTYPE html><html><head><title>Gesti&oacute; de fitxersr</title><meta charset='UTF-8'><meta name='viewport' content='width=device-width'/></head><body>");  
}

void initWifi(){
  DBG_OUTPUT_PORT.begin(115200);
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
    WiFi.softAP(ssid, password);
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
//  server.begin();


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



