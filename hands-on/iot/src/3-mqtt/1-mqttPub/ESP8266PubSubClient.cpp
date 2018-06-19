/*
 * DBLab - DBServer
 * Oficina prática de Internet das Coisas
 *
 * 06/2018
 *
 * Arquivo .cpp, implementação da classe ESP8266PubSubClient_CLASS.
 *
 */
 
/* ------------------- ESP8266PubSubClient_CLASS ------------------- */
#include "ESP8266PubSubClient.h"

ESP8266PubSubClient::ESP8266PubSubClient()
{
  pubSubClient = new PubSubClient(wifiClient);

  /* Get the MAC address of the ESP module to be used as device ID. */
  byte mac[6];
  WiFi.macAddress(mac);
  deviceID = String(mac[0], HEX) + String(mac[1], HEX) + String(mac[2], HEX) +
             String(mac[3], HEX) + String(mac[4], HEX) + String(mac[5], HEX);

}

// Função de configuração.
void ESP8266PubSubClient::setup()
{
  // Configura servidor mqtt com os parâmetros 'host' e 'porta'.
  pubSubClient->setServer(mqtt_server, mqtt_server_port);
}

// Configura a função callback na biblioteca PubSubClient.
void ESP8266PubSubClient::setCallback(MQTT_CALLBACK_SIGNATURE) 
{
  pubSubClient->setCallback(callback); 
}

// Publica mensagens.
boolean ESP8266PubSubClient::publish(const char* topic, const char* payload) 
{
  return pubSubClient->publish(topic, payload);
}

// Função para verificar conexão mqtt.
int ESP8266PubSubClient::connected() 
{
  return pubSubClient->connected();
}

// Funcão para efetuar conexão com servidor mqtt.
void ESP8266PubSubClient::connect() 
{
  // Repete até ter uma conexão efetuada.
  while (!pubSubClient->connected()) {
    Serial.print("Conectando-se ao broker MQTT...");
    // Tenta conexão.
    if (pubSubClient->connect(deviceID.c_str())) {
      Serial.println(" conectado!");

      /* TODO: quando o cliente conseguir se conectar, enviar
       *   a mensagem "ESTOU VIVO" para o tópico de saída. */
      
    } else {
      Serial.print(" falhou, rc= ");
      Serial.print(pubSubClient->state());
      Serial.println(" Tentando novamente em 5s...");
      delay(5000);
    }
  }
}

/* Função de repetição. Ela fica sendo chamada repetidamente durante a execução
 *   do programa. */
void ESP8266PubSubClient::loop() 
{
  pubSubClient->loop();
}

