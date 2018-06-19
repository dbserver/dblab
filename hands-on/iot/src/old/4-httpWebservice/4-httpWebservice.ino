/*
 * DBLab - DBServer
 * Oficina prática de Internet das Coisas
 *
 * 06/2018
 *
 *
 * EXERCÍCIO 4 CONECTIVIDADE WIFI: LIGAR LED EM OUTRO ESP8266 VIA HTTP.
 *    Neste exercício cria-se o Servidor.
 * 
 * Procure pelos TODO's no código e complete com a função necessária para
 *   implementar a função referida.
 *
 */
 
#include "ESP8266Webservice.h"
#define LED_PIN D4

ESP8266Webservice webservice;

/* Função chamada para tratar requisição HTTP do cliente. */
void httpHandler()
{
  String* state = new String("off");
  
  webservice.httpHandler(state);

  if (*state == "on")
    digitalWrite(LED_PIN, LOW);
  else if (*state == "off")
    digitalWrite(LED_PIN, HIGH);
}

 /* Função de configuração. Ela é executada uma única vez no início da execução
  *   do programa. */
void setup()
{
  Serial.begin(115200);
  delay(10);

  // Define pino do LED.
  pinMode(LED_PIN, OUTPUT);

  // Inicializa LED desligado.
  digitalWrite(LED_PIN, HIGH);

  // Configura conexão wifi.
  webservice.setup();

  // Define HttpHandler
  webservice.setHttpHandler("/led", httpHandler);

  // Inicializa WebServer.
  webservice.start();
}

/* Função de repetição. Ela fica sendo chamada repetidamente durante a execução
 *   do programa. */
void loop()
{
  webservice.handleClient();
}
