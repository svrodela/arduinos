#include "Ubidots.h"
#include "DHT.h"
#define DHTPIN 2     // Pin D4 en Wemos equivale al 2 en Arduino
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);

/****************************************
 * Define Instances and Constants
 ****************************************/

const char* UBIDOTS_TOKEN = "BBFF-HsWLrLw3unRHhxW3U1Mlmonw8S0QJf";  // Put here your Ubidots TOKEN
const char* WIFI_SSID = "INFINITUM9476_2.4"; // Put here your Wi-Fi SSID
const char* WIFI_PASS = "4sadAnZbwn"; // Put here your Wi-Fi password

Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP);

/****************************************
 * Auxiliar Functions
 ****************************************/

// Put here your auxiliar functions

/****************************************
 * Main Functions
 ****************************************/

void setup() {
  delay(10);
  dht.begin();
  Serial.begin(115200);
  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS);

  // ubidots.setDebug(true);  // Uncomment this line for printing debug messages
}

void loop() {
  //lectura de datos DHT11
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

   if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);
  Serial.print(F("Humedad: "));
  Serial.print(h);
  Serial.print(F("%  Temperatura: "));
  Serial.print(t);
  Serial.print(F("°C "));

  
  //Envio de valores a ubidots
  ubidots.add("temperatura", t);  // variables feeds
  ubidots.add("humedad", h);

  bool bufferSent = false;
  bufferSent = ubidots.send();  // Will send data to a device label that matches the device Id

  if (bufferSent) {
    // Do something if values were sent properly
    Serial.println("El dispositivo envió valores");
  }

  delay(5000);
}
