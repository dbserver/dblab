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
 
#ifndef wifi_h
#define wifi_h

#include <ESP8266WiFi.h>
#include <WiFiClient.h>

class WFclass
{
    public:
      WFclass();
      /* Inicia a conexão do cliente Wi-Fi com a rede disponível no local. */
      void setup();
      
    private:
      /* TODO: Informe aqui o nome e senha da rede Wi-Fi disponível. */
      const char* c_ssid = "";
      const char* c_pass = "";

      int status;
};

#endif

