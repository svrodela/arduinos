/* 
    Creado por: Sergio Valdez Rodela
   Insertar el valor de un sensor de temperatura(A0) desde wemos ESP8266 a php + mysql
*/

#include <ESP8266WiFi.h>

#include <ArduinoJson.h>

const char *ssid = "INFINITUM9476_2.4";
const char *password = "4sadAnZbwn";


const char* host = "https://dry-fjord-94565.herokuapp.com/data/esp32";

void setup()
{
  Serial.begin(9600);
  // conexion para wifi

  Serial.println();
  Serial.println();
  Serial.print("Conectando a: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("IP: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  
  float v = analogRead(A0); //leemos el valor analogico
 
    Serial.print("Valor: ");
    Serial.print(v);

 


  Serial.print("connectando a ");
  Serial.println(host);

  // crea la conexion con el cliente wifi
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("fallo al conectar");
    return;
  }

  // se crea la solicitud de servidor
  String url = ""; //nuestra pagina para insertar datos
   String iruido = "iruido=11&icalor=12&igas=1";
   String icalor = "icalor=";
   String igas = "igas=";
//variables JSON 

  Serial.print("Solicitando URL: ");
  Serial.println(url);

  // enviaremos la solicitud al servidor
  client.print(String("POST ") + url + iruido + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> cliente fuera de tiempo !");
      client.stop();
      return;
    }
  }

  // lee la respuesta del servidor y las muestra en el puerto serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
  Serial.println("conexion cerrada");

  delay(60000); //espera por un minuto
}
