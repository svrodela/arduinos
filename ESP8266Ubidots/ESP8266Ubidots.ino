#include "UbidotsESPMQTT.h"
/****************************************
 * Define Constants
 ****************************************/
#define TOKEN "BBFF-HsWLrLw3unRHhxW3U1Mlmonw8S0QJf" // Your Ubidots TOKEN
//#define WIFINAME "INFINITUM9476_2.4" //Your SSID
//#define WIFIPASS "4sadAnZbwn" // Your Wifi Pass
#define WIFINAME "Biblioteca" //Your SSID
#define WIFIPASS "" // Your Wifi Pass

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
  // put your setup code here, to run once:
  //client.ubidotsSetBroker("industrial.api.ubidots.com"); // Sets the broker properly for the industrial account
  client.setDebug(true); // Pass a true or false bool value to activate debug messages
  Serial.begin(115200);
  client.wifiConnection(WIFINAME, WIFIPASS);
  client.begin(callback);
  }

void loop() {
  // put your main code here, to run repeatedly:
  if(!client.connected()){
      client.reconnect();
      }
  
  float value1 = 10;//analogRead(A0);
  client.add("temperature", value1);
  client.ubidotsPublish("my-new-device");
  client.loop();
  delay(5000);
}
