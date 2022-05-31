/******************************************************************************************************************************
lectura de datos metodo GET desde API en heroku
metodo Get con descerialización con la libreria ArduinoJson
 *******************************************************************************************************************************/

#include <WiFi.h>
#include <HTTPClient.h> // nos permite hacer peticiones http
#include <ArduinoJson.h>

// credenciales de la red a la cual nos conectaremos
const char* ssid = "Tenda_3DE948";
const char* password = "18264838";

//const char* ssid = "Edificio C2";
//const char* password = "";



//configuración JSON
StaticJsonDocument<1536> doc;

// Url's para hacer las peticiones
const char* url = "https://dry-fjord-94565.herokuapp.com/ver";

String input;
const int requestInterval = 100000;  // intervalo de respuesta 7s

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
      input = getRequest(url);
      DeserializationError error = deserializeJson(doc, input);
      
      if (error) {
        Serial.print("deserializeJson() falló: ");
        Serial.println(error.c_str());
        return;
      }
      
      deserializeJson(doc, input);

     /* const char* valor=doc["icalor"];
      Serial.print("El valor es: ");*/
      Serial.print(doc.as<JsonArray>());
      for (JsonObject item : doc.as<JsonArray>()) {
  //obtiene los campos del Input Json
  long fecha_seconds = item["fecha"]["seconds"]; 
  long fecha_nanoseconds = item["fecha"]["nanoseconds"]; 
  int icalor = item["icalor"]; 
  int igas = item["igas"]; 
  int iruido = item["iruido"]; 
  //los imprime de forma secuencial
  Serial.println("***************************");
  Serial.print("Calor: ");
  Serial.print(icalor);  
  Serial.print(" Gas: ");
  Serial.print(igas);
  Serial.print(" Ruido: ");
  Serial.println(iruido);
  Serial.println("***************************");
}
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
