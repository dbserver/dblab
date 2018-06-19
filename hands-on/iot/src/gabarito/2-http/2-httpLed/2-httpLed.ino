/*
 * DBLab - DBServer
 * Oficina prática de Internet das Coisas
 *
 * 06/2018
 *
 *
 * EXERCÍCIO 2.2: SERVIÇO HTTP PARA CONTROLE DO LED
 * 
 * Este código cria um serviço HTTP e conecta-se à rede Wi-Fi disponível.
 *
 * Uma página web estará disponível no IP correspondente ao dispositivo. Abra 
 *   um navegador e digite o IP na barra de endereço.
 *
 * Aqui, continuamos usando os paradigmas de programação orientada a ojetos e 
 *   programação orientada a eventos, como visto no exemplo anterior.
 *   
 * A novidade é que agora a página, servida por este dispostivo, pode enviar
 *   requisições 'GET' ao servidor. Usaremos isto para controlar o estado de um LED.
 *   
 * Procure pelos TODO's no código e complete com a função necessária para
 *   implementar a função referida.
 * 
 */
 
#include <ESP8266WebServer.h>
#include "wifi.h"

#define LED_PIN D5

/* Define web server na porta 80 com HTTP */
ESP8266WebServer server(80);

/* Instancia o cliente Wi-Fi. */
WFclass wifi;

/* Função de configuração. Ela é executada uma única vez no início da execução
  *   do programa. */
void setup()
{
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.begin(9600);

  /* Configura o ESP8266 para atuar como cliente Wi-Fi. */
  wifi.setup();

  /* Registrando as funções de callback para as rotas desejadas: */  
  server.on("/", handleRoot); /* Rota raiz. */
  server.on("/on", handleLedOn); /* Rota /on. */
  server.on("/off", handleLedOff); /* Rota /off. */
  
  /* Finalmente inicializa o servidor webserver, com as configurações feitas. */
  server.begin();
  Serial.println("Servidor HTTP rodando...");
}
 
/* Função de repetição. Ela fica sendo chamada repetidamente durante a execução
 *   do programa. */
void loop()
{
  server.handleClient();
}
  
/* Função chamada quando cliente faz requisição URI de '/',
 * ela envia o status HTTP 200 (OK) e um texto para o 
 * browser ou cliente. (obs. status http 404 (error).) */
void handleRoot()
{
  String webString =
  "<!DOCTYPE HTML><html><head>"
  "<meta name='apple-mobile-web-app-capable' content='yes'>"
  "<style>body{background-color:#4285F4;font-size:60px;font-family:verdana;}</style>"
  "<script>"
  "function on(){window.location.assign('/on')}"
  "function off(){window.location.assign('/off')}"
  "</script>"
  "</head>"
  "<body><center>"
  "<div><bold>DBLab</bold></br>Oficina de Internet das Coisas</div>"
  "</br><div><input type='button' style='font-size:80px' value='on' onclick='on()'></br>"
  "<input type='button' style='font-size:80px' value='off' onclick='off()'></div>"
  "</center></body></html>";  
  server.send(200, "text/html", webString);
}

/* Função (callback) que é executada quando a rota '/on' é acessada. Neste caso,
 *   o LED está sendo ligado. */
void handleLedOn()
{
  digitalWrite(LED_PIN, HIGH);
  handleRoot();
}

/* Função (callback) que é executada quando a rota '/off' é acessada. Neste caso,
 *   o LED está sendo desligado. */
void handleLedOff()
{
  digitalWrite(LED_PIN, LOW);
  handleRoot();
}

