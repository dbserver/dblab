/*
 * DBLab - DBServer
 * Oficina prática de Internet das Coisas
 *
 * 06/2018
 *
 * Arquivo .cpp, implementação da classe ESP8266WebserviceClient_CLASS.
 *
 */
 
/* ------------------- ESP8266WebserviceClient_CLASS ------------------- */
#include "ESP8266WebserviceClient.h"

// Contrutor da classe
ESP8266WebserviceClient::ESP8266WebserviceClient() {}

// Efetua conexão remota ao host.
//bool ESP8266WebserviceClient::connect(const char *host, const int port)
//{
//    wifiClient.connect(host, port);
//}

void ESP8266WebserviceClient::sendRequest(String &state, const char *host)
{
    wifiClient.connect(host, port);
    
    Serial.print("Enviando requisição para o host ");
    Serial.println(host);

    // Cria-se URI para requisição.
    String url = "/led?state=" + state;

    Serial.print("GET URL: ");
    Serial.println(url);

    wifiClient.print(String("GET ") + url + " HTTP/1.1\r\n" +
                     "Host: " + host + "\r\n" +
                     "Connection: close\r\n\r\n");

    wifiClient.print(String("GET ") + url + " HTTP/1.1\r\n" +
                     "Host: " + host + "\r\n" +
                     "Connection: close\r\n\r\n");
}

