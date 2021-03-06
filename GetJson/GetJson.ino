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
StaticJsonDocument<1536> doc;


//char json[] = "{\"icalor\":\"77\",\"iruido\":\"66\",\"igas\":\"55\",\"fecha\":\"\"}";
char json[] = "{\"icalor\":\"77\",\"iruido\":\"66\",\"igas\":\"55\",\"fecha\":\"\"}";


//const char* world = doc["hello"];



// Url's para hacer las peticiones
const char* example = "https://www.google.com";

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
     // const String* input=answer;
      
     /* deserializeJson(doc, answer);

      const char* valor=doc["icalor"];
      Serial.print("El valor es: ");
      Serial.print(valor);*/
      //delay(requestInterval); 


    for (JsonObject item : doc.as<JsonArray>()) {

    long fecha_seconds = item["fecha"]["seconds"]; // 1651413600, 1651450390, 1651450791, 1651450804, ...
    long fecha_nanoseconds = item["fecha"]["nanoseconds"]; // 0, 640000000, 874000000, 804000000, 670000000, ...
  
    int icalor = item["icalor"]; // 12, 10, 10, 11, 11, 22, 10, 10, 0, 22, 22, 5
    int igas = item["igas"]; // 800, 800, 800, 11, 11, 22, 800, 800, 0, 22, 22, 25
    int iruido = item["iruido"]; // 11, 33, 33, 11, 11, 22, 33, 33, 0, 22, 22, 2

}
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
