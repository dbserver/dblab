/*
 * DBLab - DBServer
 * Oficina prática de Internet das Coisas
 *
 * 06/2018
 *
 * Arquivo .cpp, implementação da classe wifi.
 *
 */
 
#include "wifi.h"

/* Contrutor da classe. Não faz nada, só instancia o objeto */
WFclass::WFclass(){}

/* Inicia a conexão do cliente Wi-Fi com a rede disponível no local. */
void WFclass::setup()
{     
  delay(1000);
  Serial.print("Conectando na rede ");
  Serial.print(c_ssid);

  /* Inicia o cliente Wi-Fi, conectando à rede especificada, de acordo com
   *   as credenciais de acessi (SSID e senha). */
  status = WiFi.begin(c_ssid, c_pass);               

  /* O ESP tende a demorar para conectar em redes instáveis. Quando isto
   *   ocorre, a melhor alternativa é causar um reset na placa e tentar  
   *   novamente. Isto é o que o código abaixo faz. */
  for(int count=0; count<=10; count++)
  {
    if(WiFi.status() == WL_CONNECTED)
      break;
    
    delay(500);
    Serial.print(".");
    
    if(count==10)
    {
      Serial.println(" desisto :(");
      ESP.restart();
    }
  }
               
  Serial.println("Conectado: ");
  Serial.print(" MAC: ");
  Serial.println(WiFi.macAddress());
  Serial.print(" IP: ");
  Serial.println(WiFi.localIP());
  Serial.print(" Subrede: ");
  Serial.println(WiFi.subnetMask());
  Serial.print(" Gateway: ");
  Serial.println(WiFi.gatewayIP());
  Serial.print(" DNS: ");
  Serial.println(WiFi.dnsIP());
  Serial.print(" Canal: ");
  Serial.println(WiFi.channel());
  Serial.print(" Status: ");
  Serial.println(WiFi.status());
}

