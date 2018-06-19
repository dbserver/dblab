/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 */
 
#define OUTPUT_PIN 2
#define DELAY_TIME 1000

// Setup function runs once when you press reset or power the board
void setup()
{
  // Initialize digital pin 13 as an output.
  pinMode(OUTPUT_PIN, OUTPUT);
}

// Loop function runs over and over again forever
void loop()
{
  digitalWrite(OUTPUT_PIN, HIGH); // Turn the LED on (HIGH is the voltage level)
  delay(DELAY_TIME);              // Wait for a second
  digitalWrite(OUTPUT_PIN, LOW);  // Turn the LED off by making the voltage LOW
  delay(DELAY_TIME);              // Wait for a second
}
