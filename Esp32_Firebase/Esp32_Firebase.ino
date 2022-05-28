#include <WiFi.h>
#include "FirebaseESP32.h"

// Credenciales wifi
#define WIFI_SSID "Note10+"
#define WIFI_PASSWORD "123456789"

// Credenciales Proyecto Firebase
#define FIREBASE_HOST "https://region676-e21b8.firebaseio.com"
#define FIREBASE_AUTH "SQ24U3SrXqr5Rtr5XIxI4i643Xj9IFVotQo9OC7m"

// Firebase Data object
FirebaseData firebaseData;

// Si deseamos una ruta especifica
String nodo = "/ESP32_1/Sensores";

void setup() 
{
  Serial.begin(115200);
  Serial.println();

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Conectado al Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}


void loop() 
{

    // push de datos
        Firebase.pushInt(firebaseData, nodo + "/hall", hallRead());
        Firebase.pushInt(firebaseData, nodo + "/temp", hallRead());
        Serial.println(hallRead());
        delay(60000);
        //Firebase.end(firebaseData); //termina la conexión

} // End Loop
