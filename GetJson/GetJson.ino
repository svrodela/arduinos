/******************************************************************************************************************************
lectura de datos metodo GET desde API en heroku
 *******************************************************************************************************************************/

#include <WiFi.h>
#include <HTTPClient.h> // nos permite hacer peticiones http
#include <ArduinoJson.h>

// credenciales de la red a la cual nos conectaremos
const char* ssid = "Tenda_3DE948";
const char* password = "18264838";


//configuración JSON
StaticJsonDocument<200> doc; // <- a little more than 200 bytes in the stack

//char json[] = "{\"icalor\":\"77\",\"iruido\":\"66\",\"igas\":\"55\",\"fecha\":\"\"}";
char json[] = "{\"icalor\":\"77\",\"iruido\":\"66\",\"igas\":\"55\",\"fecha\":\"\"}";


//const char* world = doc["hello"];



// Url's para hacer las peticiones
const char* example = "https://dry-fjord-94565.herokuapp.com/ver";

String answer;
const int requestInterval = 7000;  // intervalo de respuesta 7s

float sensorReadingsArr[4];

void setup(){
    Serial.begin(115200);

    // conexión a la red
    WiFi.begin(ssid, password);
    Serial.println("Connecting");
    while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
    }
    Serial.println("");
    Serial.print("Conectado a la red con la IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();
    
} // EOF setup

void loop(){
    if(WiFi.status()== WL_CONNECTED ){ 
      answer = getRequest(example);
      Serial.println("\nRespuesta de heroku");
      
      Serial.println(answer);

      
      deserializeJson(doc, json);

      const char* valor=doc["icalor"];
      Serial.print("El valor es: ");
      Serial.print(valor);
      delay(requestInterval);     
    }


} 

//Funcion para atender peticiones 
String getRequest(const char* serverName) {
  HTTPClient http;    
  http.begin(serverName);
  
  // Enviamos peticion HTTP
  int httpResponseCode = http.GET();
  
  String payload = "..."; 
  
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // liberamos
  http.end();

  return payload;
}
