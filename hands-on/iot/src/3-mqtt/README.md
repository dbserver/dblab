# Oficina prática de Internet das Coisas

## Parte 3: Comunicação via protocolo MQTT

Já tendo estabelecida a comunicação do ESP8266 com a Internet através da rede Wi-Fi, agora é a hora de utilizarmos o protocolo MQTT, em substituição ao HTTP.

Estes exercícios foram idealizados para demonstrar na prática a utilização do protocolo de comunicação assíncrona MQTT que é largamente utilizado por devices IoT. A tecnologia MQTT é baseada em um padrão de comunicação no estilo _publisher/subscriber_, organizado em filas. As filas de comunicação são denominadas tópicos e seus nomes podem ser organizados de forma hierárquica tornando claro seu propósito.

Estaremos utilizando um broker público (iot.eclipse.org), possibilitando que estes projetos possam ser executados em qualquer ambiente, com conectividade à Internet

### Exercícios:
1. **Cliente MQTT Simples** (diretório _1-mqttPub_)
 * Este código cria um cliente MQTT, conecta-se em um _broker_, e envia dados simples a ele, através do tópico de saída _"dblab/hands-on/mqtt/out"_.

2. **Cliente MQTT pub/sub** (diretório _2-mqttPubSub_)
 * Aqui utilizaremos dois tópicos:
   * Um tópico de saída: _"dblab/hands-on/mqtt/out"_, onde o estado do botão será publicado.
   * Um tópico de entrada: _"dblab/hands-on/mqtt/in"_, que receberá comandos para ligar/desligar o LED.
