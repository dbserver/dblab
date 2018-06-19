/*
 * DBLab - DBServer
 * Oficina prática de Internet das Coisas
 *
 * 06/2018
 *
 *
 * EXERCÍCIO 1.3: COMUNICAÇÃO SERIAL
 *
 * Abra o monitor serial na IDE Arduino para visualizar as mensagens
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

  /* Inicializando a porta serial com baud rate de 9600. */
  Serial.begin(9600);

  Serial.println("DBServer | DBLab | Procergs");
  Serial.println("Oficina prática de Internet das Coisas");
}

/* Função de repetição. Ela fica sendo chamada repetidamente durante a execução
 *   do programa. */
void loop()
{
  bool buttonState = digitalRead(BUTTON_PIN);

  digitalWrite(LED_PIN, buttonState);

  if(buttonState == HIGH)
    Serial.println("O LED está ligado.");
  else
    Serial.println("O LED está desligado.");

  delay(100); /* dá um tempo para o processador respirar... */
}
