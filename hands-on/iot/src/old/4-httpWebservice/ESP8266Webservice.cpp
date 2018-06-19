/*
 * DBLab - DBServer
 * Oficina prática de Internet das Coisas
 *
 * 06/2018
 *
 * Arquivo .cpp, implementação da classe wifi.
 *
 */
 
/* ------------------- ESP8266Webservice_CLASS ------------------- */
#include "ESP8266Webservice.h"

// Contrutor da classe
ESP8266Webservice::ESP8266Webservice()
{
    webServer = new ESP8266WebServer(port);
}

// Função de configuração.
void ESP8266Webservice::setup()
{
    // Inicializa módulo wifi.
    setup_wifi();
}

// Inicializa WebServer.
void ESP8266Webservice::start()
{
    // Inicializa módulo wifi.
    ((ESP8266Webservice *)this)->webServer->begin();
    Serial.println("Server started");
    Serial.println(WiFi.localIP());
}

// Define rotas httpHandler
void ESP8266Webservice::setHttpHandler(const char *route, HTTP_HANDLER_SIGNATURE)
{
    ((ESP8266Webservice *)this)->webServer->on(route, httpHandler);
}

// Manipula requisições de clientes
void ESP8266Webservice::handleClient()
{
    ((ESP8266Webservice *)this)->webServer->handleClient();
}

// httpHandler
void ESP8266Webservice::httpHandler(String* state)
{
  *state = ((ESP8266Webservice *)this)->webServer->arg("state");

  ((ESP8266Webservice *)this)->webServer->send(200, "text/plain", "Led is now " + *state);
}

// Inicializa módulo wifi.
void ESP8266Webservice::setup_wifi()
{
    delay(10);
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}
