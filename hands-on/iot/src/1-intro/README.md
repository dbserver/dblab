# Oficina prática de Internet das Coisas

## Parte 1: programação básica com o ESP8266

Neste primeiro exercício veremos como ler e escrever nas portas digitais do ESP8266.

### Exercícios:
1. **Blink** (diretório _1-blink_):
   * Como primeiro exercício, aqui montaremos um circuito composto de um LED e um resistor
   * O software traz conceitos básicos de programação com a arquitetura Arduino (_Wiring_), bem como as funções principais (_setup_, _loop_, _pinMode_ e _digitalWrite_).
   

2. **Botão e LED** (diretório _2-buttonLed_):
   * Adicionaremos um _push-button_ ao circuito;
   * O código é bastante baseado no primeiro exercício, mas agora traz o uso da função _digitalRead_ para receber o estado de um botão, e então refletir este estado no LED.
   
3. **Comunicação serial** (diretório _3-serial_):
   * Usaremos aqui algumas funções para comunicação de mensagens via porta USB com o PC, onde a placa ESP8266 está conectada.
   