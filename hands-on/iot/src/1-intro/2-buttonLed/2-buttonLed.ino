#define LED_PIN D5
#define BUTTON_PIN D0

 /* Função de configuração. Ela é executada uma única vez no início da execução
  *   do programa. */
void setup()
{
  pinMode(LED_PIN, OUTPUT);
  
  /* TODO: Configure o pino do botão como uma entrada. */
}

/* Função de repetição. Ela fica sendo chamada repetidamente durante a execução
 *   do programa. */
void loop()
{
  bool buttonState = digitalRead(BUTTON_PIN);

  digitalWrite(LED_PIN, buttonState);

  delay(10); /* Dá um tempo para o processador respirar... */
}
