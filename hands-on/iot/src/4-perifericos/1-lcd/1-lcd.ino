/*
 * DBLab - DBServer
 * Oficina prática de Internet das Coisas
 *
 * 06/2018
 *
 *
 * EXERCÍCIO 1 PERIFÉRICOS: DISPLAY LCD.
 * 
 * Procure pelos TODO's no código e complete com a função necessária para
 *   implementar a função referida.
 *
 */
#include "wifi.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "ESP8266PubSubClient.h"

// Configura o LCD display.
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define MESSAGE_MAX_SIZE 50

WFclass wifi;
ESP8266PubSubClient mqttClient;

char msg[MESSAGE_MAX_SIZE];
int value = 0;
long lastMsg = 0;
int cursor_line = 0;

 /* Função de configuração. Ela é executada uma única vez no início da execução
  *   do programa. */
void setup()
{
  Serial.begin(9600);

  wifi.setup();
  mqttClient.setup();
  mqttClient.connect();
  
  // Define a função 'callback' para receber mensagens.
  mqttClient.setCallback(callback);

  // Inicializa o display LCD.
  lcd.begin();
  
  // Liga o LED e mostra uma mensagem.
  lcd.backlight();
  lcd.print("DBLAB HANDS-ON");
}

/* Função de repetição. Ela fica sendo chamada repetidamente durante a execução
 *   do programa. */
void loop()
{
  if (!mqttClient.connected()) mqttClient.connect();
  mqttClient.loop();
}

// Função para limpar caracteres do display.
void clearLcd(int len)
{
  for(int i=0; i<len; i++) lcd.print(" ");
}

// Função callback, aqui chegam as mensagens do tópico inscrito.
void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  
  char msg[length+1];
  memcpy(msg, payload,length); // Trata mensagem.
  msg[length]=0;
  Serial.print(msg);

  /* Compara mensagens, para assim, posicionar corretamente
   * nas posições definidas do display. */
  if(!strncmp(msg, "T", 1)) 
  {
    clearLcd(strlen(msg));
    lcd.setCursor(0, 0);
  }
  else if(!strncmp(msg, "H", 1)) 
  {
    clearLcd(strlen(msg));
    lcd.setCursor(8, 0);
  }
  else if(!strncmp(msg, "D", 1)) 
  {
    clearLcd(strlen(msg));
    lcd.setCursor(0, 1);
  }

  lcd.printstr(msg);
 
  Serial.println();
}

