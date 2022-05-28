#include <Arduino.h>
#include <WiFi.h>
//#include <ESP32Ping.h>
//#include <HTTPClient.h>
#include <ArduinoJson.h>

// Deklarasi Variable dan Konstanta
String wifiSSID = "INFINITUM9476_2.4";
String wifiPassword = "4sadAnZbwn";
//const IPAddress routerIp(192, 168, 0, 1);
String googlDotCom = "www.google.com";

// Deklarasi Fungsi
void connectWifi();
void getHttp();
void postHttp();

void setup()
{
  Serial.begin(9600);
  connectWifi();
  // getHttp();
  postHttp();
}

void loop()
{
}

void postHttp()
{
  String url = "https://dry-fjord-94565.herokuapp.com/data/esp32";
  HTTPClient http;
  String response;

  StaticJsonDocument<200> buff;
  String jsonParams;
  buff["icalor"] = "22";
  buff["iruido"] = "22";
  buff["igas"] = "22";

  serializeJson(buff, jsonParams);
  Serial.println(jsonParams);

  http.begin(url);
  http.addHeader("Content-Type", "application/json");
  http.POST(jsonParams);
  response = http.getString();
  Serial.println(response);
}

void getHttp()
{
  String url = "https://dry-fjord-94565.herokuapp.com/data/esp32";
  HTTPClient http;
  String response;

  http.begin(url);
  http.GET();

  response = http.getString();
  Serial.println(response);

  StaticJsonDocument<1024> doc;
  deserializeJson(doc, response);
  JsonObject obj = doc.as<JsonObject>();

  String data = obj[String("data")];
  String support = obj[String("support")];

  Serial.println(data);
  Serial.println(support);
}

void connectWifi()
{
  Serial.println("Connectado al wifi");
  WiFi.begin(wifiSSID.c_str(), wifiPassword.c_str());
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  Serial.println("Wifi conectado");
  Serial.println(WiFi.SSID());
  Serial.println(WiFi.RSSI());
  Serial.println(WiFi.macAddress());
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.gatewayIP());
  Serial.println(WiFi.dnsIP());

  if (Ping.ping(googlDotCom.c_str()))
  {
    Serial.println("Connectado a Internet");
  }
}
