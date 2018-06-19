/*
 * DBLab - DBServer
 * Oficina prática de Internet das Coisas
 *
 * 06/2018
 *
 *
 * EXERCÍCIO 2 PERIFÉRICOS: SENSOR DE DISTÂNCIA.
 * 
 * Procure pelos TODO's no código e complete com a função necessária para
 *   implementar a função referida.
 *
 */

#include "wifi.h"
#include "ESP8266PubSubClient.h"
#include <hcsr04.h>

#define TRIG_PIN D5
#define ECHO_PIN D6
#define MESSAGE_MAX_SIZE 50

// Configura o sensor de distãncia.
HCSR04 hcsr04(TRIG_PIN, ECHO_PIN, 20, 4000);

WFclass wifi;
ESP8266PubSubClient mqttClient;
int lastTimeMsg = 0;

/* Função de configuração. Ela é executada uma única vez no início da execução
 *   do programa. */
void setup()
{
  Serial.begin(9600);

  wifi.setup();
  mqttClient.setup();
}

/* Função de repetição. Ela fica sendo chamada repetidamente durante a execução
 *   do programa. */
void loop()
{
  if (!mqttClient.connected()) mqttClient.connect();
  mqttClient.loop();

  /* A cada 500 milisegundos publica-se a distância lida pelo sensor. */
  long now = millis();  
  if (now - lastTimeMsg > 500)
  {
    lastTimeMsg = now;
   
    int distance = hcsr04.distanceInMillimeters();
    char msg[MESSAGE_MAX_SIZE] = "";
    snprintf (msg, MESSAGE_MAX_SIZE, "Dist: %ldmm", distance);
    Serial.println(msg);
    mqttClient.publish(MQTT_OUT_TOPIC, msg);
  }
}
