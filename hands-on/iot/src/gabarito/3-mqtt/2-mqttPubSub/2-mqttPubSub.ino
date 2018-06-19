/*
 * DBLab - DBServer
 * Oficina prática de Internet das Coisas
 *
 * 06/2018
 *
 *
 * EXERCÍCIO 3.1: CLIENTE MQTT QUE PUBLICA E SE INSCREVE EM TÓPICOS
 * 
 * Este código cria um cliente MQTT e conecta-se em um broker. Dois
 *   tópicos são usados: um de saída, para escrever o estado do botão,
 *   e outro de entrada, para atuar sobre o LED.
 * 
 * Procure pelos TODO's no código e complete com a função necessária para
 *   implementar a função referida.
 */

#include "wifi.h"
#include "ESP8266PubSubClient.h"

#define LED_PIN D5
#define BUTTON_PIN D0

WFclass wifi;
ESP8266PubSubClient mqttClient;

int currentButtonState = LOW;

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
  mqttClient.setup();
  mqttClient.connect();

  // Define a função 'callback' para receber mensagens.
  mqttClient.setCallback(callback);
}

/* Função de repetição. Ela fica sendo chamada repetidamente durante a execução
 *   do programa. */
void loop()
{
  if(!mqttClient.connected()) mqttClient.connect();
  mqttClient.loop();

  int buttonState = digitalRead(BUTTON_PIN);
  if(buttonState != currentButtonState)
  {
    delay(50);
    buttonState = digitalRead(BUTTON_PIN);
    if(buttonState != currentButtonState)
    {
      currentButtonState = buttonState;
      
      String message("Meu botão está ");
      if(buttonState == LOW)
        message += String("desligado.");
      else
        message += String("ligado.");

      mqttClient.publish(MQTT_OUT_TOPIC, message.c_str());

      /* TODO: publique o estado do botão no tópico de entrada, com
       *   mensagens "on" e "off". */
      if(buttonState == LOW) mqttClient.publish(MQTT_IN_TOPIC, "off");
      else mqttClient.publish(MQTT_IN_TOPIC, "on");
      
      Serial.println("Mensagem publicada: " + message);
    }
  }
  delay(10);
}

// Função callback, aqui chegam as mensagens do tópico inscrito.
void callback(char *topic, byte *payload, unsigned int length)
{
  char message[length+1];
  memcpy(message, payload, length);
  message[length]=0;
  
  Serial.print("Mensagem recebida: ");
  Serial.println(message);

  // Caso a mensagem comece com 1, liga o LED.
  //if ((char)payload[0] == '1')
  if(!strncmp(message, "on", 2))
  {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("O LED está ligado!");
  }
  else if(!strncmp(message, "off", 3))
  {
    digitalWrite(LED_PIN, LOW);
    Serial.println("O LED está desligado!");
  }
}

