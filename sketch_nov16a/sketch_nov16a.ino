// C++ code
//
#include "arduino_secrets.h" //Wifi SSID & Wachtwoord
#include <WiFiS3.h>
#include <ArduinoMqttClient.h>


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
}

void loop() {
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
   
}