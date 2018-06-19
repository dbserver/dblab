/*
 * DBLab - DBServer
 * Oficina prática de Internet das Coisas
 *
 * 06/2018
 *
 *
 * EXERCÍCIO 4 PERIFÉRICOS: SENSOR DE TEMPERATURA.
 * 
 * Procure pelos TODO's no código e complete com a função necessária para
 *   implementar a função referida.
 *
 */

#include "wifi.h"
#include <DHT.h>
#include "ESP8266PubSubClient.h"

#define MESSAGE_MAX_SIZE 50

#define DHTPIN D1     // Define pino data do DHT.
#define DHTTYPE DHT11   // Define o modelo do DHT, 11 (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Inicializa sensor de temperatura DHT.

WFclass wifi;
ESP8266PubSubClient mqttClient;

/* Função de configuração. Ela é executada uma única vez no início da execução
  *   do programa. */
void setup()
{
  // Inicializa sensor de temperatura.
  dht.begin();
  
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

    /* Rotina para tratar valores lido pelo sensor e assim publicar via mqtt. */
    float hum = dht.readHumidity();
    float temp = dht.readTemperature();
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.println(" Celsius");

    char humidity[MESSAGE_MAX_SIZE] = "";
    char temperature[MESSAGE_MAX_SIZE] = "";

    snprintf (temperature, MESSAGE_MAX_SIZE, "T: %02dC", (int)temp);
    //temperature[5] = 0xDF;
    
    snprintf (humidity, MESSAGE_MAX_SIZE, "H: %02d%%", (int)hum);
    
    mqttClient.publish(MQTT_OUT_TOPIC, humidity);
    delay(2000);
    mqttClient.publish(MQTT_OUT_TOPIC, temperature);
}

