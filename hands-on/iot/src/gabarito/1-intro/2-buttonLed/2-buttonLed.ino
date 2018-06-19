/*
 * DBLab - DBServer
 * Oficina prática de Internet das Coisas
 *
 * 06/2018
 *
 *
 * EXERCÍCIO 1.2: BOTÃO E LED
 *
 * Procure pelos TODO's no código e complete com a função necessária para
 *   implementar a função referida.
 *
 */
 
 #define LED_PIN D5
 #define BUTTON_PIN D0

 /* Função de configuração. Ela é executada uma única vez no início da execução
  *   do programa. */
void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
}

/* Função de repetição. Ela fica sendo chamada repetidamente durante a execução
 *   do programa. */
void loop()
{
  bool buttonState = digitalRead(BUTTON_PIN);

  digitalWrite(LED_PIN, buttonState);

  delay(10); /* Dá um tempo para o processador respirar... */
}
