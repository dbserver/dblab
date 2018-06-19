# Oficina prática de Internet das Coisas

## Parte 2: Comunicação HTTP

A segunda parte utiliza o protocolo HTTP, comumente utilizado para estabelecer comunicação entre clientes e servidores na Internet. Com o uso da rede Wi-Fi, iremos desenvolver os seguintes exercícios

### Exercícios:
1. **Serviço HTTP simples** (diretório _1-httpServer_):
 * Este código cria um serviço HTTP e conecta-se à rede Wi-Fi disponível. Aqui, utiliza-se dois conceitos importantes em programação:
     - Programação orientada a eventos, onde uma função (callback) é executada toda vez que um determinado evento ocorre. Neste caso, toda vez que um site é acessado por um cliente (browser), o programa responde com o conteúdo requisitado. Ver função handleRoot() e server.on().
     - Programação orientada a objetos: é quando utilizamos 'objetos' são utilizados para representar dados, atributos, métodos ou estados. Assim, ao se criar um novo objeto de um determinado tipo, aquela variável passa a possuir todos os atributos e métodos associados ao seu tipo de objeto. Ver, por exemplo, o objeto ESP8266WebServer e seus métodos begin, on e send. 

2. **Serviço HTTP para controle de um LED** (diretório _2-httpLed_):
 * Este código cria um serviço HTTP e conecta-se à rede Wi-Fi disponível. 
 * Uma página web estará disponível no IP correspondente ao dispositivo. Abra um navegador e digite o IP na barra de endereço.
 * Aqui, continuamos usando os paradigmas de programação orientada a objetos e programação orientada a eventos, como visto no exemplo anterior. A novidade é que agora a página, servida por este dispositivo, pode enviar requisições 'GET' ao servidor. Usaremos isto para controlar o estado de um LED.

3. **Serviço HTTP para controle de um LED** (diretório _3-httpButtonLed_):
 * Este código age como um servidor e cliente HTTP ao mesmo tempo. Como servidor, ele disponibiliza um LED para ser controlado pela internet, aguardando clientes conectarem-se e enviarem requisições. Como cliente, ele envia requisições 'GET' para outro servidor, a partir do estado de seu botão.
 * Aqui, continuamos usando os paradigmas de programação orientada a objetos e programação orientada a eventos, como visto no exemplo anterior.
