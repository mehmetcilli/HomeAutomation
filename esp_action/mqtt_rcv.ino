#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
const char* ssid     = "WLAN1-GJF9HN";
const char* password = "nd10y3728LrRmeq2";
const char* mqttServer = "192.168.8.107";
const int mqttPort = 1883;
const char* mqttUser = "actor";
const char* mqttPassword = "lector";
int entrer;

// PARTIE ANALOG



WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
 
  Serial.begin(9600);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("Actor", mqttUser, mqttPassword )) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
 
  client.subscribe("order/light");
 pinMode(5,OUTPUT);

}
 
void callback(char* topic, byte* payload, unsigned int length) {
  
  if ((char)payload[0] == 'T' && (char)payload[1] == 'r' && (char)payload[2] == 'u' && (char)payload[3] == 'e'){
    digitalWrite(5,HIGH);
    delay(10);
  }

  else{
    digitalWrite(5,LOW);
  }
}

void loop() {
  
  client.loop();
}
