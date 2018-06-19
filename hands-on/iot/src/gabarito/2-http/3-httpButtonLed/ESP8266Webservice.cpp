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

// Inicializa WebServer.
void ESP8266Webservice::start()
{
    webServer->begin();
    Serial.print("Servidor iniciado em: ");
    Serial.println(WiFi.localIP());
}

// Define rotas httpHandler
void ESP8266Webservice::setHttpHandler(const char *route, HTTP_HANDLER_SIGNATURE)
{
  webServer->on(route, httpHandler);
}

// Manipula requisições de clientes
void ESP8266Webservice::handleClient()
{
  webServer->handleClient();
}

// httpHandler
void ESP8266Webservice::httpHandler(String &state)
{
  Serial.print("Recebendo requisição de ");
  Serial.println(webServer->client().remoteIP());
 
  state = webServer->arg("state");
  webServer->send(200, "text/plain", "Led esta agora " + state);
}

