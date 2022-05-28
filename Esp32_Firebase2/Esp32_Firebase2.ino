#include <WiFi.h>
#include "FirebaseESP32.h"

// Credenciales wifi
#define WIFI_SSID "nombre de la red"
#define WIFI_PASSWORD "password"

// Credenciales Proyecto Firebase
#define FIREBASE_HOST "link de la bd"
#define FIREBASE_AUTH "token de la bd"

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
