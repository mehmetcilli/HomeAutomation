
#include <ESP8266WiFi.h>
#include <ESP8266Ping.h>
#include <Wire.h>


const char* ssid     = "Mehmet";
const char* password = "mehmetizzy";
IPAddress ip (192, 168, 43, 116); // adresses des serveurs de League Of Legends




int avg_ms, x;
String avg_ms_str;

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println();


  Serial.println();
  Serial.println("Connecting to WiFi");

  WiFi.begin(ssid, password);


  while (WiFi.status() != WL_CONNECTED) {

    delay(100);
  }
}


void loop() {

  if ( Ping.ping(ip, 2)) {
    avg_ms = Ping.averageTime();
    
    Serial.println(avg_ms);
  }


}

