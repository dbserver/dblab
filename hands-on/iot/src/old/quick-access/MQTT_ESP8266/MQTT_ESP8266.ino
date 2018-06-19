/*
 Basic ESP8266 MQTT example

 This sketch demonstrates the capabilities of the pubsub library in combination
 with the ESP8266 board/library.

 It connects to an MQTT server then:
  - publishes "Hello World" to the topic "mqtt_out_topic" every two seconds
  - subscribes to the topic "mqtt_in_topic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary
  - If the first character of the topic "mqtt_in_topic" is an 1, switch ON the ESP Led,
    else switch it off

 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.
*/
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define BAUD_RATE 115200
#define MESSAGE_MAX_SIZE 50
#define OUTPUT_PIN 2

// Update these with values suitable for your network.
const char* ssid = "DBLABDevices";
const char* password = "@rdu!n0$";
const char* mqtt_server = "192.168.10.18";
const int mqtt_server_port = 31223;
const char* mqtt_in_topic = "/dblab/hands-on/mqtt/esp8266/helloworld/in";
const char* mqtt_out_topic = "/dblab/hands-on/mqtt/esp8266/helloworld/out";

WiFiClient wifiClient;
PubSubClient client(wifiClient);
char msg[MESSAGE_MAX_SIZE];
int value = 0;
long lastMsg = 0;

// Initialize WIFI Module
void setup_wifi() {
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

// Callback function for incoming messages
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(OUTPUT_PIN, LOW); // Turn the LED on (LOW is the voltage level)
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)
  } else {
    digitalWrite(OUTPUT_PIN, HIGH); // Turn the LED off (HIGH is the voltage level)
  }
}

// Function used to reconnect WIFI Module
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish(mqtt_out_topic, "hello world");
      // ... and resubscribe
      client.subscribe(mqtt_in_topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

// Setup function runs once when you press reset or power the board
void setup() {
  // Setup serial port baud rate
  Serial.begin(BAUD_RATE);
  
  // Initialize digital pin 13 as an output.
  pinMode(OUTPUT_PIN, OUTPUT);
  
  // Initialize WIFI Module
  setup_wifi();

  // Setup mqtt server host and port
  client.setServer(mqtt_server, mqtt_server_port);

  // Setup mqtt callback function for incoming messages
  client.setCallback(callback);
}

// Loop function runs over and over again forever
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, 75, "Hello World #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish(mqtt_out_topic, msg);
  }
}
