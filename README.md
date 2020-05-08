# HomeAutomation
This is a project of home automation which is able to control lights, heating and blinds.
It will use Raspeberry Pi interface as an MQTT broker.
ESP8266 as data sender.
And some sensors to acquire datas.

-------------UPDATE----------------
The file sensor_config.ino is the connection of the ESP8266 to the WIFI network & MQTT broker.
Moreover, it reads an analog input from A0 and send the value to the MQTT server.
There is a subscription at esp/test and write down the value there.
