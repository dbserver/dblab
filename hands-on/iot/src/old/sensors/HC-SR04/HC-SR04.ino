#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <hcsr04.h>

#define TRIG_PIN 14
#define ECHO_PIN 12
#define BUZZER_PIN 13
#define BAUD_RATE 115200
#define MESSAGE_MAX_SIZE 50
#define OUTPUT_PIN 2

struct NoteStruct
{
  int A = 550;
  int As = 582;
  int B = 617;
  int C = 654;
  int Cs = 693;
  int D = 734;
  int Ds = 777;
  int E = 824;
  int F = 873;
  int Fs = 925;
  int G = 980;
  int Gs = 1003;
  int A2 = 1100;
  int A2s = 1165;
  int B2 = 1234;
  int C3 = 1308;
  int C3s = 1385;
  int D3 = 1555;
} Note;

struct NoteLengthStruct
{
  float half = 0.5;
  float one = 1.0;
  float one_half = 1.5;
  float two = 2.0;
  float two_half = 2.5;
} NoteLength;

HCSR04 hcsr04(TRIG_PIN, ECHO_PIN, 20, 4000);
int tempo = 400;

// Update these with values suitable for your network.
const char *ssid = "DBLABDevices";
const char *password = "@rdu!n0$";
const char *mqtt_server = "192.168.10.18";
const int mqtt_server_port = 31223;
const char *mqtt_in_topic = "/dblab/hands-on/mqtt/esp8266/sensor/presence/in";
const char *mqtt_out_topic = "/dblab/hands-on/mqtt/esp8266/sensor/presence/out";

WiFiClient wifiClient;
PubSubClient client(wifiClient);
char msg[MESSAGE_MAX_SIZE];
int value = 0;
long lastMsg = 0;

// Initialize WIFI Module
void setup_wifi()
{
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

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

// Function used to reconnect WIFI Module
void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client"))
    {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish(mqtt_out_topic, "hello world");
      // ... and resubscribe
      client.subscribe(mqtt_in_topic);
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setTone(int pin, int note, int duration)
{
  tone(pin, note, duration);
  delay(duration);
  noTone(pin);
}

void setup()
{
  // Setup serial port baud rate
  Serial.begin(BAUD_RATE);

  pinMode(OUTPUT_PIN, OUTPUT);

  // Initialize digital pin 13 as an output.
  pinMode(BUZZER_PIN, OUTPUT);

  // Initialize WIFI Module
  setup_wifi();

  // Setup mqtt server host and port
  client.setServer(mqtt_server, mqtt_server_port);

  // Setup mqtt callback function for incoming messages
  client.setCallback(callback);
}

void loop()
{
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();

  int distance = hcsr04.distanceInMillimeters();

  snprintf (msg, MESSAGE_MAX_SIZE, "{\"Distance\": \"%ld\" }", distance);

  Serial.println(msg);

  client.publish(mqtt_out_topic, msg);

  setTone(BUZZER_PIN, Note.D3, distance * NoteLength.two);

  delay(250);
}
