// C++ code
#include "arduino_secrets.h" //Wifi SSID & Wachtwoord
#include <WiFiS3.h>
#include <ArduinoMqttClient.h>

//Variabelen voor WiFi en MQTT-verbinding

const char BROKER[] = "192.168.144.1";
const int PORT = 1883;
const char PUBLISH_TOPIC[] = "rensbroersma/moisture";
const char SUBSCRIBE_TOPIC[] = "dionstroet/temperatuur";
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

//Variabelen voor sensor en pomp
int soilMoisture = 0;
int in1 = 2;
int pin1 = A0;
int sensor1Value = 0;
int lightPin = 4;


void setup() 
{
    Serial.begin(9600);

    pinMode(in1, OUTPUT);

    pinMode(pin1, INPUT);

    pinMode(lightPin, OUTPUT);

    delay(5000);

    //Wifi-verbinding
    while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
      delay(5000);
    }
    Serial.println("wifi connected");

    //MQTT-verbinding 
    bool MQTTconnected = false;
    while (!MQTTconnected) {
      if (!mqttClient.connect(BROKER, PORT))
      delay(1000);
    else
    MQTTconnected = true;
    }
    Serial.println("mqtt connected");


    mqttClient.onMessage(OnMqttMessage);
    mqttClient.subscribe(SUBSCRIBE_TOPIC);
}

//Werking pomp
void loop() {
  mqttClient.poll();
   Serial.print("Moisture Level:");
   sensor1Value = analogRead(pin1);
   Serial.println(sensor1Value);

   if (sensor1Value == 0) 
   {
      digitalWrite(in1, HIGH);
       Serial.println("Pomp uit, geen input");
       digitalWrite(4, HIGH);
   } 
   else if (sensor1Value < 450)
   {
       digitalWrite(in1, LOW);
       
       
       Serial.println("Pomp aan");
   }
   else 
   {
       digitalWrite(in1, HIGH);
       Serial.println("Pomp uit");
       
       
   }
   
   
   //Bericht publiceren naar MQTT-server 
   mqttClient.beginMessage(PUBLISH_TOPIC,true,0);
   mqttClient.print(sensor1Value);
   mqttClient.endMessage();
   delay(1000);
}

//Bericht ontvangen van MQTT-server
void OnMqttMessage(int messageSize) { 
    Serial.print("Received a message with topic '");
    Serial.println(mqttClient.messageTopic());
    float num;
    //Serial.println(mqttClient.read());
    String message = "";
    while (mqttClient.available()) {
      message.concat((char)mqttClient.read()); 
      }
      Serial.println(message);
    num = message.toFloat();
    Serial.println(num);
      if (num > 25.0){
        digitalWrite(lightPin, HIGH);
      }
      else{
        digitalWrite(lightPin, LOW);
      }
}


   


   

