// C++ code
//
#include "arduino_secrets.h" //Wifi SSID & Wachtwoord
#include <WiFiS3.h>
#include <ArduinoMqttClient.h>

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);
const char broker[] = "192.168.144.1";
const int port = 1883;
const char topic[] = "rensbroersma/moisture";

int Moisture = 0;
int IN1 = 2;
int Pin1 = A0;
int sensor1Value = 0;

void setup() 
{
    Serial.begin(9600);

    pinMode(IN1, OUTPUT);

    pinMode(Pin1, INPUT);

    digitalWrite(IN1, HIGH);

    delay(500);

    while (WiFi.begin(ssid, pass) != WL_CONNECTED) {delay(5000);
    }
    Serial.println("wifi connected");
    bool MQTTconnected = false;
    while (!MQTTconnected) {if (!mqttClient.connect(broker, port))delay(1000);

    else
    MQTTconnected = true;
    
    }
    Serial.println("mqtt connected");
}

void loop() {
  mqttClient.poll();
   Serial.print("Moisture Level:");
   sensor1Value = analogRead(Pin1);
   Serial.println(sensor1Value);

   if (sensor1Value == 0) 
   {
      digitalWrite(IN1, LOW);
       Serial.println("Pomp uit, geen input");
   } 
   else if (sensor1Value > 450)
   {
       digitalWrite(IN1, LOW);
       
       Serial.println("Pomp uit");
   }
   else 
   {
       digitalWrite(IN1, HIGH);
       Serial.println("Pomp aan");
       
       
   }
   
   //sensor1Value
   mqttClient.beginMessage(topic,true,0);
   mqttClient.print(sensor1Value);
   mqttClient.endMessage();
   delay(1000);
}

