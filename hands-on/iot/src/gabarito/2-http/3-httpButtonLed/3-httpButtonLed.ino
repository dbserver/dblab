/*
 * DBLab - DBServer
 * Oficina prática de Internet das Coisas
 *
 * 06/2018
 *
 *
 * EXERCÍCIO 2.3: SERVIÇO HTTP PARA COMUNICAÇÃO ENTRE DISPOSITIVOS
 * 
 * Este código age como um servidor e cliente HTTP ao mesmo tempo. Como
 *   servidor, ele disponibiliza um LED para ser controlado pela internet,
 *   aguardndo clientes conectarem-se e enviarem requisições. Como cliente,
 *   ele envia requisições GET para outro servidor, a partir do estado de
 *   seu botão.
 * 
 * Aqui, continuamos usando os paradigmas de programação orientada a ojetos e 
 *   programação orientada a eventos, como visto no exemplo anterior.
 *   
 * Procure pelos TODO's no código e complete com a função necessária para
 *   implementar a função referida.
 */

#include "wifi.h"
#include "ESP8266Webservice.h"
#include "ESP8266WebserviceClient.h"

#define LED_PIN D5
#define BUTTON_PIN D0

/* Endereço do servidor do LED que queremos acionar. */
const char *host = "192.168.101.84";

bool currentButtonState = LOW;

/* Instancia o cliente Wi-Fi. */
WFclass wifi;

/* Instancia um serviço web. */
ESP8266Webservice webservice;

/* Instancia um cliente web. */
ESP8266WebserviceClient webserviceClient;

 /* Função de configuração. Ela é executada uma única vez no início da execução
  *   do programa. */
void setup()
{
  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT);
  digitalWrite(BUTTON_PIN, LOW);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  
  wifi.setup();

  webservice.setHttpHandler("/led", httpHandler);
  webservice.start();
}

void loop()
{
  webservice.handleClient();

  int buttonState = digitalRead(BUTTON_PIN);
  if(buttonState != currentButtonState)
  {
    /* Aguarda um pouco para filtrar o ruído do botão... */
    delay(50);
    buttonState = digitalRead(BUTTON_PIN);
    if(buttonState != currentButtonState)
    {
      currentButtonState = buttonState;
      
      String state;
      if(buttonState == HIGH) state = "on";
      else state = "off";

      Serial.println("Botão está agora " + state);

      webserviceClient.sendRequest(state, host);      
  
      Serial.println();
    }
  }

  delay(10); /* Dá um tempo para o processador respirar... */
}

/* Função chamada para tratar requisição HTTP do cliente. */
void httpHandler()
{
  String state;
  
  webservice.httpHandler(state);

  if(state == "on")
    digitalWrite(LED_PIN, HIGH);
  else if(state == "off")
    digitalWrite(LED_PIN, LOW);

  Serial.println("Led está agora " + state);
  Serial.println();
}

