/*
 * DBLab - DBServer
 * Oficina prática de Internet das Coisas
 *
 * 06/2018
 *
 *
 * EXERCÍCIO 1.1: BLINK
 *
 * Modifique a localização do LED no circuito e altere o valor da variável
 *   LED_PIN apropriadamente. Também veja o efeito do valor da variável
 *   DELAY_TIME no comportamento do circuito.
 *
 */

#define LED_PIN D5
#define DELAY_TIME 1000

/* Função de configuração. Ela é executada uma única vez no início da execução
 *   do programa. */
void setup()
{
  pinMode(LED_PIN, OUTPUT);
}

/* Função de repetição. Ela fica sendo chamada repetidamente durante a execuçãonce
 *   do programa. */
void loop()
{
  digitalWrite(LED_PIN, HIGH);
  delay(DELAY_TIME);

  digitalWrite(LED_PIN, LOW);
  delay(DELAY_TIME);
}
