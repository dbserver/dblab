#include "wifi.h"
#include "ESP8266PubSubClient.h"

#define LED_PIN D5
#define BUTTON_PIN D0

WFclass wifi;
ESP8266PubSubClient mqttClient;

int currentButtonState = LOW;

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

  mqttClient.setCallback(callback);
}

void loop()
{
  if(!mqttClient.connected()) mqttClient.connect();
  mqttClient.loop();

  int buttonState = digitalRead(BUTTON_PIN);
  if(buttonState != currentButtonState) {
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

      /* TODO: publique o estado do botão no tópico de entrada,
       *   com mensagens "on" e "off". */
             
      Serial.println("Mensagem publicada: " + message);
    }
  }
  delay(10);
}

void callback(char *topic, byte *payload, unsigned int length)
{
  char message[length+1];
  memcpy(message, payload, length);
  message[length]=0;
  
  Serial.print("Mensagem recebida: ");
  Serial.println(message);

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

