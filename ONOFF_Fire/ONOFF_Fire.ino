#include <WiFi.h>
#include "FirebaseESP32.h"

// Credenciales wifi
#define WIFI_SSID "INFINITUM9476_2.4"
#define WIFI_PASSWORD "4sadAnZbwn"

// Credenciales Proyecto Firebase
#define FIREBASE_HOST "https://region676-e21b8.firebaseio.com"
#define FIREBASE_AUTH "SQ24U3SrXqr5Rtr5XIxI4i643Xj9IFVotQo9OC7m"

// Firebase Data object
FirebaseData firebaseData;
String fireStatus = "";  // estado del led en Firebase
int led = 2;                                                               

void setup() {

  Serial.begin(9600);

  delay(1000);

  pinMode(2, OUTPUT);                

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); //intenta conectarse al wifi

  Serial.print("Conectando a");

  Serial.print(WIFI_SSID);

  while (WiFi.status() != WL_CONNECTED) {

    Serial.print(".");

    delay(500);

  }

  Serial.println();

  Serial.print("Conectado a ");

  Serial.println(WIFI_SSID);

  Serial.print("Tu dirección IP: ");

  Serial.println(WiFi.localIP());   //imprime la I¨P
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);   // Se conecta a firebase

  Firebase.setString(firebaseData,"LED", "ON"); //envia un valor inicial a firebase ON

}

void loop() {

  fireStatus = Firebase.getString(firebaseData,"/LED"); // obtiene el valor del led
  Serial.println(firebaseData.stringData()); 
  if (firebaseData.stringData() == "ON") {  // verifica en firebase si está el valor en ON  para encender el led localmente

    Serial.println("Led ON");                 

    digitalWrite(2, HIGH); // Enciende el led

  }

  else if (firebaseData.stringData() == "OFF") {     //compara el valor OFF en firebase

    Serial.println("Led OFF");

    digitalWrite(2, LOW);//apaga el led

  }

  else { //si lee valores distintos imprime el mensaje

    Serial.println("Credenciales erroneas! Envía ON/OFF");

  }

}
