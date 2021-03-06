/***************************************************
  Adafruit MQTT Library ESP8266 Ejemplo
  Sergio Valdez Rodela
 ****************************************************/
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"


/**************************************************/
#include "DHT.h"
#define DHTPIN 2     // Pin D4 en Wemos equivale al 2 en Arduino
#define DHTTYPE DHT11  

DHT dht(DHTPIN, DHTTYPE);

// Lamp pin
const int lamp_pin = 4;

#define PHOTOCELL       A0  // analog 0

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "INFINITUM9476_2.4"
#define WLAN_PASS       "4sadAnZbwn"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "svrodela"
#define AIO_KEY         "8e241d1f0cc046b5b48261339b24e941"
/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/


// Setup a feed called 'photocell' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish temperatura = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Temperatura");
Adafruit_MQTT_Publish humedad = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Humedad");


/*************************** Sketch Code ************************************/


void onoffcallback(char *data, uint16_t len) {
  Serial.print("Hey we're in a onoff callback, the button value is: ");
  Serial.println(data);

     String message = String(data);
      message.trim();
      if (message == "ON") {digitalWrite(lamp_pin, HIGH);}
      if (message == "OFF") {digitalWrite(lamp_pin, LOW);}
  
}


void setup() {
 dht.begin();

 
    pinMode(lamp_pin, OUTPUT);

    
  Serial.begin(115200);
  delay(10);

  Serial.println(F("Adafruit MQTT demo"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());


  //onoffbutton.setCallback(onoffcallback);

 // mqtt.subscribe(&onoffbutton);

}

uint32_t x=0;

void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();


/*++++++++++++++++++++++++++++Sensor DHT11*************/
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
  Serial.print(F("??C "));
  /*******************************************************/
  
  Serial.print(F("\nSending temperatura val "));
  Serial.print(t);
  Serial.print("...");
  if (! temperatura.publish(t)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }
  Serial.print(F("\nSending humedad val "));
  Serial.print(h);
  Serial.print("...");
  if (! humedad.publish(h)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }

delay(120000); //espera 120 segundos

  // this is our 'wait for incoming subscription packets and callback em' busy subloop
  // try to spend your time here:
  mqtt.processPackets(500);
  
  // ping the server to keep the mqtt connection alive
  // NOT required if you are publishing once every KEEPALIVE seconds
  
 // if(! mqtt.ping()) {
 //   mqtt.disconnect();
 // }
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 10 seconds...");
       mqtt.disconnect();
       delay(10000);  // wait 10 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
