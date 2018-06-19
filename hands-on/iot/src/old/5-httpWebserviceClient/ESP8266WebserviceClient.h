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
        // Configura ESP8266Webservice
        void setup();
        // Efetua conexão remota para o host.
        bool connect(const char* host, const int port);
        // Função sendRequest.
        void sendRequest(String* state, const char* host);
    private:
        // Configura e inicializa módulo wifi.
        void setup_wifi();
    
        // Define parâmetros de conexão.
        const char* ssid = "DBDevices";
        const char* password = "!mP@db@dM";
        WiFiClient wifiClient;
};
