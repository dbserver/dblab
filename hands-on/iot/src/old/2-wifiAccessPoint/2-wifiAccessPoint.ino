/*
 * DBLab - DBServer
 * Oficina prática de Internet das Coisas
 *
 * 06/2018
 *
 *
 * EXERCÍCIO 2.2: SERVIDOR HTTP E ACCESS POINT WI-FI
 *
 * Este código cria um serviço HTTP e uma rede Wi-Fi, agindo como access point.
 *
 * No seu dispositivo Wi-Fi, procure pela rede criada e entre com a senha
 *   corresponde. Depois, abra um navegador e digite o IP.
 *   
 * Procure pelos TODO's no código e complete com a função necessária para
 *   implementar a função referida.
 *
 */
 
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

/* Essas são as configurações do WiFi access point. */
const char* ssid = "Trinity";
const char* password = "Morpheus";

/* Define web server na porta 80 com HTTP */
ESP8266WebServer server(80); 

/* Função chamada quando cliente faz requisição URI de '/',
 * ela envia o status HTTP 200 (OK) e um texto para o 
 * browser ou cliente. (obs. status http 404 (error).) */
void handleRoot() 
{
  server.send(200, "text/plain", "There is no spoon.");
}

 /* Função de configuração. Ela é executada uma única vez no início da execução
  *   do programa. */
void setup(void)
{
  Serial.begin(9600);

 /* Configura esp8266 no modo AcessPoint,
  * caso desejas uma rede aberta, basta remover o parâmetro 'password'. */
  WiFi.mode(WIFI_AP); 
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP(); 
  Serial.print("HotSpt IP:");
  Serial.println(myIP);
 
 /* Esta função se define as rotas de acesso.
  * Por exemplo, quando um cliente pede '/' se define o caminho 'handleRoot'. */
  server.on("/", handleRoot);

 /* Finalmente inicializa o Servidor, webserver, com as configurações feitas. */
  server.begin();  
}

/* Função de repetição. Ela fica sendo chamada repetidamente durante a execução
 *   do programa. */
void loop(void)
{
  server.handleClient(); 
}
