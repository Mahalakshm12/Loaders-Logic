#include<Servo.h>
#include<SoftwareSerial.h>
Servo s1;
#define RX 9
#define TX 10
int gas_sensor = A0;
int buzzer = 4;
const int fanPin=5;
SoftwareSerial sim(RX, TX);


void setup() 
{
  Serial.begin(9600);
  pinMode(gas_sensor, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(fanPin,OUTPUT);
  s1.attach(3);
}

void loop() 
{
  int value = analogRead(gas_sensor);
  Serial.print("Gas Sensor Value : ");
  Serial.print(value);

  if(value > 400)
  {
    digitalWrite(buzzer, HIGH);
    digitalWrite(fanPin,HIGH);
    Serial.println("  Gas Detected");
    delay(500);
    s1.write(0);
  delay(1000);
  s1.write(180);
  delay(1000);
  s1.write(0);
  digitalWrite(fanPin,HIGH);
  delay(5000);
  digitalWrite(fanPin,LOW);
  delay(5000);
  
}
  if (buzzer == HIGH) {
    // Send SMS
    sim.println("AT+CMGF=1"); // Set SMS mode
    sim.println("AT+CMGS=\"+911234567890\"\r"); // Replace with authorized person's number
    sim.println("LPG Gas Leak Detected!"); // SMS content
    sim.println((char)26); // Send SMS
  
  delay(500);
  
  }else
  {
    digitalWrite(buzzer, LOW);
    digitalWrite(fanPin, LOW);
    
    Serial.println("  Gas Not Detected");
    delay(500);
  }
}