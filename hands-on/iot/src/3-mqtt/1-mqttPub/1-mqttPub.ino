/*
 * DBLab - DBServer
 * Oficina prática de Internet das Coisas
 *
 * 06/2018
 *
 *
 * EXERCÍCIO 3.1: CLIENTE MQTT SIMPLES 
 * 
 * Este código cria um cliente MQTT, conecta-se em um broker, e
 *   envia dados simples a ele.
 *
 * Procure pelos TODO's no código e complete com a função necessária para
 *   implementar a função referida.
 */

#include "wifi.h"
#include "ESP8266PubSubClient.h"

WFclass wifi;

ESP8266PubSubClient mqttClient;

int value = 0;
long lastTimeMsg = 0;

 /* Função de configuração. Ela é executada uma única vez no início da execução
  *   do programa. */
void setup()
{
  Serial.begin(9600);

  wifi.setup();
  mqttClient.setup();
  mqttClient.connect();
}

/* Função de repetição. Ela fica sendo chamada repetidamente durante a execução
 *   do programa. */
void loop()
{
  if(!mqttClient.connected()) mqttClient.connect();
  mqttClient.loop();

  long now = millis();
  if (now - lastTimeMsg > 2000)
  {
    lastTimeMsg = now;
    
    /* Publica um "Hello World" a cada 2 segundos... */
    ++value;
    String message("Hello World! #");
    message += String(value, DEC);
    mqttClient.publish(MQTT_OUT_TOPIC, message.c_str());

    Serial.println("Mensagem publicada: " + message);
  }
}


