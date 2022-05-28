/****************************************
 * ADAPTACIÓN L.I SERGIO VALDEZ RODELA
 ****************************************/
#include "UbidotsESPMQTT.h"
#include "DHT.h"
#define DHTPIN 2     // Pin D4 en Wemos equivale al 2 en Arduino
#define DHTTYPE DHT11  

DHT dht(DHTPIN, DHTTYPE);

/****************************************
 * CONSTANTES
 ****************************************/
#define TOKEN "BBFF-HsWLrLw3unRHhxW3U1Mlmonw8S0QJf" // Your Ubidots TOKEN
#define WIFINAME "INFINITUM9476_2.4" //Your SSID
#define WIFIPASS "4sadAnZbwn" // Your Wifi Pass

Ubidots client(TOKEN);

/****************************************
 * Auxiliar Functions
 ****************************************/

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

/****************************************
 * Main Functions
 ****************************************/

void setup() {

  
  delay(10);
  dht.begin();
  Serial.begin(115200);
  
  //client.ubidotsSetBroker("industrial.api.ubidots.com"); // Sets the broker properly for the industrial account
  client.setDebug(true); // Pass a true or false bool value to activate debug messages
  Serial.begin(115200);
  client.wifiConnection(WIFINAME, WIFIPASS);
  client.begin(callback);
  }

void loop() {


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

  if(!client.connected()){
      client.reconnect();
      }
  
  client.add("temperatura", t);
  client.ubidotsPublish("PlacaWemos");
  client.loop();
}
