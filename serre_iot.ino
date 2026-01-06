#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

// Config WiFi & MQTT
const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(15, DHT22);

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(2, OUTPUT); // Pompe (LED Blue)
  pinMode(4, OUTPUT); // Fan (LED Red)

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
  client.setServer(mqtt_server, 1883);
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP32_Serre_Final_User")) {
      Serial.println("Connecté au Broker MQTT!");
    } else { delay(5000); }
  }
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  float t = dht.readTemperature();
  float h = dht.readHumidity();

  // Automation Locale
  if(t > 30.0) digitalWrite(4, HIGH); else digitalWrite(4, LOW); // Temp > 30 -> Fan ON
  if(h < 40.0) digitalWrite(2, HIGH); else digitalWrite(2, LOW); // Hum < 40 -> Pompe ON

  // Envoi JSON vers Cloud
  String payload = "{\"temp\":" + String(t) + ", \"sol\":" + String(h) + "}";
  client.publish("ma_serre/data", payload.c_str());

  Serial.println("Data envoyée: " + payload);
  delay(5000);
}