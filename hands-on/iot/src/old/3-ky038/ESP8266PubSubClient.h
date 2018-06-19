/*
 * DBLab - DBServer
 *
 * Oficina prática de Internet das Coisas
 *
 * 05/2018
 */
 
/* ------------------- ESP8266PubSubClient_CLASS ------------------- */
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define MQTT_IN_TOPIC "/dblab/hands-on/mqtt/esp8266/sensor/ky038/in"
#define MQTT_OUT_TOPIC "/dblab/hands-on/mqtt/esp8266/gateway/in"
#define MQTT_CLIENT_ID "ESP8266KY038"

#ifdef ESP8266
#include <functional>
#define MQTT_CALLBACK_SIGNATURE std::function<void(char*, uint8_t*, unsigned int)> callback
#else
#define MQTT_CALLBACK_SIGNATURE void (*callback)(char*, uint8_t*, unsigned int)
#endif

class ESP8266PubSubClient
{
    public:
        ESP8266PubSubClient();
        // Setup PubSubClient
        void setup();
        // Initialize WIFI Module
        void setup_wifi();
        // Set callback function for incoming messages
        void setCallback(MQTT_CALLBACK_SIGNATURE);
        // Publish messages
        boolean publish(const char* topic, const char* payload);
        // Function used to test connection
        int connected();
        // Function used to reconnect WIFI Module
        void reconnect();
        // Loop Function
        void loop();
    private:
        // Update these with values suitable for your network.
        const char* ssid = "DBDevices";
        const char* password = "!mP@db@dM";
        const char* mqtt_server = "192.168.10.18";
        const int mqtt_server_port = 31223;
        WiFiClient wifiClient;
        PubSubClient* pubSubClient;

};

//#endif
