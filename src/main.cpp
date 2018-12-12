#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>
#include "credentials.h"

#define MDNS_NAME "alarm"

void wifiSetup();
void serverSetup();
void handleRequest();
String getMimeType(String path);
bool streamFile(String path);
void serveRoot();
void notFound();


ESP8266WebServer server(80);

void setup()
{
    Serial.begin(115200);
    Serial.println();

    Serial.println("Waiting for owner to open serial monitor");
    delay(5000);


    wifiSetup();
    serverSetup();
}

void loop()
{
    server.handleClient();
}



void wifiSetup()
{
    Serial.println("Server setup");
    WiFi.mode(WIFI_STA);
    int status = WL_IDLE_STATUS;
    int i = 0;
    while (status != WL_CONNECTED)
    {
        status = WiFi.begin(ssid, password);
        Serial.println("Try: " + String(i++) + " Status: " + status);
        delay(3000);
    }
    Serial.println("WiFi connection established.");
    Serial.print("IP:");
    Serial.println(WiFi.localIP());

    bool mdns_success = MDNS.begin(MDNS_NAME);
    if (mdns_success)
    {
        Serial.println("MDNS server started: " + String(MDNS_NAME) + ".local");
    }
}

//webserver
void serverSetup()
{
    server.on("/", HTTP_GET, []() { serveRoot(); });
    // Handle all other requests
    server.onNotFound([]() { handleRequest(); });

    server.begin();
    Serial.println("Server started. \n");
}

void serveRoot()
{
    streamFile("/public/index.html");
}

void handleRequest()
{
    if (!streamFile(server.uri()))
    {
        notFound();
    }
}

bool streamFile(String path)
{
    Serial.println("Client requesting: " + path);
    String mimeType = getMimeType(path);
    String filename = path + ".gz";
    if (SPIFFS.exists(filename))
    {
        File file = SPIFFS.open(filename, "r");
        server.streamFile(file, mimeType);
        file.close();
        return true;
    }
    Serial.println("File did not exist: " + filename);
    return false;
}

String getMimeType(String path)
{
    if (path.endsWith(".html"))
        return "text/html";
    else if (path.endsWith(".js"))
        return "application/javascript";
    else if (path.endsWith(".css"))
        return "text/css";
    else
        return "text/plain";
}

void notFound()
{
    server.send(404, "text/plain", "Sorry, that file doesn't exist.");
}
