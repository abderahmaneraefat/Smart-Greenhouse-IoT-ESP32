#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(15, DHT22);


float lastT = 0, lastH = 0;
int lastS = 0, lastL = 0;

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(2, OUTPUT);  // Pompe
  pinMode(4, OUTPUT);  // Fan
  pinMode(5, OUTPUT);  // Light
  pinMode(18, OUTPUT); // Alerte LED
  pinMode(21, OUTPUT); // Buzzer
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
  client.setServer(mqtt_server, 1883);
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP32_Smart_Serre_2026")) {
      Serial.println("MQTT Connected!");
    } else { delay(3000); }
  }
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  float t = dht.readTemperature();
  float h = dht.readHumidity();
  int s = analogRead(32);
  int l = analogRead(34);

  if (isnan(t) || isnan(h)) return;
  digitalWrite(4, (t > 30.0) ? HIGH : LOW);
  digitalWrite(2, (s > 2500) ? HIGH : LOW);
  digitalWrite(5, (l > 2000) ? HIGH : LOW);
  
  if (t > 35.0) { digitalWrite(18, HIGH); tone(21, 1000); } 
  else { digitalWrite(18, LOW); noTone(21); }

  if (abs(t - lastT) >= 0.5 || abs(h - lastH) >= 1.0 || abs(s - lastS) >= 50 || abs(l - lastL) >= 50) {
    lastT = t; lastH = h; lastS = s; lastL = l;

    String payload = "{\"temp\":" + String(t) + ",\"hum\":" + String(h) + ",\"soil\":" + String(s) + ",\"light\":" + String(l) + "}";
    client.publish("serre/data", payload.c_str());
    
    Serial.println("Change detected! Data sent: " + payload);
  }

  delay(200); // Check très rapide pour l'interactivité
}
