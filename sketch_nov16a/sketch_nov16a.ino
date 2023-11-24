// C++ code
//
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
   Serial.print("Plant 1 - Moisture Level:");
   sensor1Value = analogRead(Pin1);
   Serial.println(sensor1Value);

   if (sensor1Value == 0) 
   {
       digitalWrite(IN1, HIGH);
       Serial.println("Pomp uit, geen input");
   } 
   else if (sensor1Value < 300)
   {
       digitalWrite(IN1, HIGH); //High = pomp is uit 
       delay (5000);
       digitalWrite(IN1, LOW); //Low = pomp is aan 
       delay (5000);
       Serial.println("Pomp aan");
   }
   else 
   {
       digitalWrite(IN1, HIGH);
       Serial.println("Pomp uit");
       
       
   }
   
}