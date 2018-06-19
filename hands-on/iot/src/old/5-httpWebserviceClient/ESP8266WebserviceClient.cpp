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

// Função de configuração.
void ESP8266WebserviceClient::setup()
{
    // Inicializa módulo wifi.
    setup_wifi();
}

// Efetua conexão remota ao host.
bool ESP8266WebserviceClient::connect(const char *host, const int port)
{
    return this->wifiClient.connect(host, port);
}

/* Função de repetição. Ela fica sendo chamada repetidamente durante a execução
 *   do programa. */
void ESP8266WebserviceClient::sendRequest(String *state, const char *host)
{
    Serial.println("eventHandler: state = " + *state);

    // Cria-se URI para requisição.
    String url = "/led?state=" + *state;

    Serial.print("Requesting URL: ");
    Serial.println(url);

    this->wifiClient.print(String("GET ") + url + " HTTP/1.1\r\n" +
                           "Host: " + host + "\r\n" +
                           "Connection: close\r\n\r\n");

    this->wifiClient.print(String("GET ") + url + " HTTP/1.1\r\n" +
                           "Host: " + host + "\r\n" +
                           "Connection: close\r\n\r\n");
}

// Inicializa módulo wifi.
void ESP8266WebserviceClient::setup_wifi()
{
    delay(10);
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.mode(WIFI_STA);
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
