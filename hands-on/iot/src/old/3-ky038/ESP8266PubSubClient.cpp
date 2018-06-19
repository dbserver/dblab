  /*
 * DBLab - DBServer
 *
 * Oficina prática de Internet das Coisas
 *
 * 05/2018
 */
 
/* ------------------- ESP8266PubSubClient_CLASS ------------------- */
#include "ESP8266PubSubClient.h"

ESP8266PubSubClient::ESP8266PubSubClient(){
  pubSubClient = new PubSubClient(wifiClient);
}

// Setup function runs once when you press reset or power the board
void ESP8266PubSubClient::setup() {
  // Initialize WIFI Module
  setup_wifi();

  // Setup mqtt server host and port
  ((ESP8266PubSubClient*)this)->pubSubClient->setServer(mqtt_server, mqtt_server_port);
}

// Setup PubSubClient Callback Function
void ESP8266PubSubClient::setCallback(MQTT_CALLBACK_SIGNATURE) {
  ((ESP8266PubSubClient*)this)->pubSubClient->setCallback(callback); 
}

// Publish messages
boolean ESP8266PubSubClient::publish(const char* topic, const char* payload) {
  return ((ESP8266PubSubClient*)this)->pubSubClient->publish(topic, payload);
}

// Initialize WIFI Module
void ESP8266PubSubClient::setup_wifi(){
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

// Function used to test connection
int ESP8266PubSubClient::connected() {
  return ((ESP8266PubSubClient*)this)->pubSubClient->connected();
}

// Function used to reconnect
void ESP8266PubSubClient::reconnect() {
  // Loop until we're reconnected
  while (!((ESP8266PubSubClient*)this)->pubSubClient->connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (((ESP8266PubSubClient*)this)->pubSubClient->connect(MQTT_CLIENT_ID)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      ((ESP8266PubSubClient*)this)->pubSubClient->publish(MQTT_OUT_TOPIC, "hello world");
      // ... and resubscribe
      ((ESP8266PubSubClient*)this)->pubSubClient->subscribe(MQTT_IN_TOPIC);
    } else {
      Serial.print("failed, rc=");
      Serial.print(((ESP8266PubSubClient*)this)->pubSubClient->state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void ESP8266PubSubClient::loop() {
    ((ESP8266PubSubClient*)this)->pubSubClient->loop();
}

