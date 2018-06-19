/*
 * DBLab - DBServer
 * Oficina prática de Internet das Coisas
 *
 * 06/2018
 *
 *
 * EXERCÍCIO 5 CONECTIVIDADE WIFI: LIGAR LED EM OUTRO ESP8266 VIA HTTP.
 *    Neste exercício cria-se o cliente.
 * 
 * Procure pelos TODO's no código e complete com a função necessária para
 *   implementar a função referida.
 *
 */
 
#include "ESP8266WebserviceClient.h"

#define LED_PIN D4
#define BUTTON_PIN D0

const char *host = "192.168.101.105";
const int port = 80;
String *state = new String("off");
bool pendingRequest = false;

ESP8266WebserviceClient webserviceClient;

/* Função chamada para tratar envio  */
void eventHandler()
{
  // Envio de comando remoto pendente.
  pendingRequest = true;

  // Leitura do estado do botão:
  int buttonState = digitalRead(BUTTON_PIN);
  //String *state = new String("off");

  // Confere o estado do botão:
  if (buttonState == HIGH)
  {
    // Liga o LED:
    *state = "on";
    digitalWrite(LED_PIN, LOW);
  }
  else
  {
    // Desliga o LED:
    *state = "off";
    digitalWrite(LED_PIN, HIGH);
  }
}

 /* Função de configuração. Ela é executada uma única vez no início da execução
  *   do programa. */
void setup()
{
  Serial.begin(115200);

  // Configura conexão wifi.
  webserviceClient.setup();

  // Define pino do LED.
  pinMode(LED_PIN, OUTPUT);

  // Define botão.
  pinMode(BUTTON_PIN, INPUT);

  // Define um evento para alterações do botão.
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), eventHandler, CHANGE);
}

/* Função de repetição. Ela fica sendo chamada repetidamente durante a execução
 *   do programa. */
void loop()
{
  // Envia requisições pendentes ao host.
  if (pendingRequest && webserviceClient.connect(host, port))
  {
    webserviceClient.sendRequest(state, host);
    pendingRequest = false;
  }

  delay(10); /* Dá um tempo para o processador respirar... */
}
