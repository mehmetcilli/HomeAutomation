#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
const char* ssid     = "WLAN1-GJF9HN";
const char* password = "nd10y3728LrRmeq2";
const char* mqttServer = "192.168.8.107";
const int mqttPort = 1883;
const char* mqttUser = "YourMqttUser";
const char* mqttPassword = "YourMqttUserPassword";
int entrer;

// PARTIE ANALOG
const int analogInPin = A0;  // ESP8266 Analog Pin ADC0 = A0
int sensorValue = 0;
char*numberString = new char[5];
int m,c,d,u;


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
 
    //if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
    if (client.connect("ESP8266Client")) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
 
  client.publish("esp/test", "Hello world");
  client.subscribe("esp/test");
 
}
 
void callback(char* topic, byte* payload, unsigned int length) {
  
  /*
  if ((char)payload[0] == 'p' && (char)payload[1] == 'i' ){
    
    for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    }
    client.publish("esp/test", "po");
  }
  */
/* 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
 
  Serial.println();
  Serial.println("-----------------------");
 */
 
}

void loop() {
  int m;
  client.loop();
  sensorValue = analogRead(analogInPin);
  Serial.println(sensorValue);


  m = (sensorValue/1000);
  sensorValue = sensorValue -m*1000;

  c= (sensorValue/100);
  sensorValue = sensorValue -c*100;

  d=(sensorValue/10);
  sensorValue = sensorValue -d*10;

  u=(sensorValue);
  
  numberString[0] = (char)(m + 48);
  numberString[1] = (char)(c + 48);
  numberString[2] = (char)(d + 48);
  numberString[3] = (char)(u + 48);
  numberString[4] = '\0';
  
  Serial.println(numberString);
  Serial.println();

  client.publish("esp/test", numberString);
  
  delay(1000);

  
}
