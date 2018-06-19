/*
 * DBLab - DBServer
 * Oficina prática de Internet das Coisas
 *
 * 06/2018
 *
 * Arquivo .h, header, define da interface dos
 * metodos publicos, variáveris e constantes 
 * privadas da classe ESP8266WebserviceClient_CLASS.
 *
 */
 
/* ------------------- ESP8266WebserviceClient_CLASS ------------------- */
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

class ESP8266WebserviceClient
{
    public:
      ESP8266WebserviceClient();
      // Efetua conexão remota para o host.
      //bool connect(const char* host, const int port);
      // Função sendRequest.
      void sendRequest(String &state, const char* host);
    private:
      const int port = 80;
      WiFiClient wifiClient;
};
