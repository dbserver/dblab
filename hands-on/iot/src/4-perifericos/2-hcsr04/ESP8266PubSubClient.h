/*
 * DBLab - DBServer
 * Oficina prática de Internet das Coisas
 *
 * 06/2018
 *
 * Arquivo .h, header, define da interface dos
 * metodos publicos, variáveris e constantes 
 * privadas da classe ESP8266PubSubClient_CLASS.
 *
 */
  
/* ------------------- ESP8266PubSubClient_CLASS ------------------- */
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define MQTT_IN_TOPIC "dblab/hands-on/mqtt/in"
#define MQTT_OUT_TOPIC "dblab/hands-on/mqtt/display"

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
        // Configura PubSubClient
        void setup();
        // Configura callback para tratar mensagens.
        void setCallback(MQTT_CALLBACK_SIGNATURE);
        // Função para publicar mensagens.
        boolean publish(const char* topic, const char* payload);
        // Função para verificar conexão.
        int connected();
        // Funcão para efetuar conexão com servidor mqtt.
        void connect();
        // Função de repetição.
        void loop();
    private:
      String deviceID;
        /* Definição dos parâmetros de comunicação MQTT (servidor e porta).
         *   Valores possíveis:
         *     dbs-dblab-k8s.dbserver.com.br:30844 (broker interno, sem segurança)
         *     iot.eclipse.org:1883 (broker público, sem segurança)
         *     iot.eclipse.org:8883 (broker público, COM segurança) */
        const char* mqtt_server = "iot.eclipse.org";
        const int mqtt_server_port = 8883; 

        /* Se estamos usando comunicação segura (TLS), devemos usar o objeto
         *   WiFiClientSecure abaixo, no lugar do WiFiClient.
         *   (https://github.com/knolleary/pubsubclient/issues/84). */
        //WiFiClient wifiClient;
        WiFiClientSecure wifiClient;
        PubSubClient* pubSubClient;
};

