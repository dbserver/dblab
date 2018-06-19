/*
 * DBLab - DBServer
 * Oficina prática de Internet das Coisas
 *
 * 06/2018
 *
 * Arquivo .h, header, define da interface dos
 * metodos publicos, variáveris e constantes 
 * privadas da classe wifi.
 *
 */
 
/* ------------------- ESP8266Webservice_CLASS ------------------- */
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#ifdef ESP8266
#include <functional>
#define HTTP_HANDLER_SIGNATURE std::function<void()> httpHandler
#else
#define HTTP_HANDLER_SIGNATURE void (*httpHandler)()
#endif

class ESP8266Webservice
{
    public:
        ESP8266Webservice();
        // Configura ESP8266Webservice
        void setup();
        // Inicializa Webservice
        void start();
        // Define rotas httpHandler
        void setHttpHandler(const char* route, HTTP_HANDLER_SIGNATURE);
        // Handle Client
        void handleClient();
        // Http httpHandler
        void httpHandler(String* state);
        // Retorna estado do LED 
        String getState();

    private:
        // Configura e inicializa módulo wifi.
        void setup_wifi();
    
        // Define parâmetros de conexão.
        const char* ssid = "DBDevices";
        const char* password = "!mP@db@dM";
        const int port = 80;
        WiFiClient wifiClient;
        ESP8266WebServer* webServer;
};

//#endif
