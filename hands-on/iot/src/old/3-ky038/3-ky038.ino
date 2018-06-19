/*
 * DBLab - DBServer
 *
 * Oficina prática de Internet das Coisas
 *
 * 05/2018
 */
#include "ESP8266PubSubClient.h"

#define BAUD_RATE 9600
#define MESSAGE_MAX_SIZE 50
#define OUTPUT_PIN 2

ESP8266PubSubClient client;
char msg[MESSAGE_MAX_SIZE];
int value = 0;
long lastMsg = 0;

//Definicao pinos leds
int green_led = 3;
int yellow_led = 4;
int red_led = 5;

//Definicao pinos sensor
int analog_input = A0;
//int digital_input = D0;

int intensity = 0;

// Callback function for incoming messages
void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1')
  {
    digitalWrite(OUTPUT_PIN, LOW); // Turn the LED on (LOW is the voltage level)
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)
  }
  else
  {
    digitalWrite(OUTPUT_PIN, HIGH); // Turn the LED off (HIGH is the voltage level)
  }
}

void setup()
{
  // Setup serial port baud rate
  Serial.begin(BAUD_RATE);

  // Define leds as output
  pinMode(green_led, OUTPUT);
  pinMode(yellow_led, OUTPUT);
  pinMode(red_led, OUTPUT);
  
  // Define sensor as input
  pinMode(analog_input, INPUT);
  //pinMode(digital_input, INPUT);

  // Setup mqtt client
  client.setup();

  // Setup mqtt callback function for incoming messages
  client.setCallback(callback);
}

void loop()
{
  if (!client.connected())
  {
    client.reconnect();
  }
  client.loop();

  long now = millis();

  if (now - lastMsg > 2000)
  {
    lastMsg = now;
    ++value;

    intensity = analogRead(analog_input);
  
    snprintf(msg, MESSAGE_MAX_SIZE, "Noise: %ld", intensity);
      
    Serial.println(msg);
    client.publish(MQTT_OUT_TOPIC, msg);
  
    // Low Intensity
    if (intensity > 20 && intensity < 300)
    {
      digitalWrite(green_led, HIGH);
      digitalWrite(yellow_led, LOW);
      digitalWrite(red_led, LOW);
    }
    
    // Mediun Intensity
    if (intensity > 301 && intensity < 700)
    {
      digitalWrite(green_led, HIGH);
      digitalWrite(yellow_led, HIGH);
      digitalWrite(red_led, LOW);
    }
    
    // High Intensity
    if (intensity > 701)
    {
      digitalWrite(green_led, HIGH);
      digitalWrite(yellow_led, HIGH);
      digitalWrite(red_led, HIGH);
    }
    
    delay(50);
    
    // Turn off all leds
    digitalWrite(green_led, LOW);
    digitalWrite(yellow_led, LOW);
    digitalWrite(red_led, LOW);
  }
}
