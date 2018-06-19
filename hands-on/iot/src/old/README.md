# DBLAB HANDS-ON

O propósito destes experimentos é proporcionar de forma simples e didática um primeiro contato com algumas tecnologias utilizadas no dia-a-dia do DBLAB.

## Quick Access

Neste módulo inicial teremos um primeiro contato com a estrutura de um programa em Arduino, suportado pela ferramenta Arduino IDE e o módulo ESP8266-12E, também conhecido como NodeMCU. Este módulo possui conectividade WIFI 2.4 GHz e é bastante utilizado pela comunidade para prototipação de experimentos.

### Exemplo Blink

    O projeto Arduino Blink basicamente faz o LED do módulo ESP8266 piscar a cada segundo. Neste projeto simples é possível identificar a estrutura básica de um programa em Arduino, sendo composta por duas funções:
    
        * setup(): executada apenas uma vez ao energizar a placa e/ou a cada vez que o firmware da placa é resetado através do botão reset.
        
        * loop(): compreende o ciclo de execução do programa, que no caso do exemplo Blink tem duração de 2 segundos, onde o LED alterna-se entre os estados ligado/desligado a cada segundo.


### Exemplo MQTT_ESP8266

    O projeto MQTT_ESP8266 foi idealizado para demonstrar na prática a utilização do protocolo de comunicação assíncrona MQTT que é largamente utilizado por devices IoT. A tecnologia MQTT é baseada em um padrão de comunicação no estilo publisher/subscriber organizado em filas. As filas de comunicação são denominadas tópicos e seus nomes podem ser organizados de forma hierárquica tornando claro seu propósito.
    
        Neste exemplo em específico os nomes dos tópicos foram organizados da seguinte forma "/<organização>/<projeto>/<hardware>/<modulo-hands-on>/<input> | <output>":
        
        * /dblab/hands-on/mqtt/esp8266/helloworld/in: tópico para as mensagens recebidas pelo esp8266 ".
        
        * /dblab/hands-on/mqtt/esp8266/helloworld/out: tópico para as mensagens de saída a partir do esp8266.


