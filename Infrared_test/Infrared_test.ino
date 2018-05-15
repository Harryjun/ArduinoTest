//本历程为红外对管测试程序
#include <Servo.h>

Servo myservo;  // create servo 
int Infrared= 14;
int Led = 11;
int sensorValue = 0;
int flag = 0;
const byte interruptPin = 2;


void setup() {
  // put your setup code here, to run once:
  pinMode(Infrared,INPUT);
  pinMode(Led,OUTPUT);
  Serial.begin(9600);
   myservo.attach(9);
   digitalWrite(Led,HIGH); 

   pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(1)
  {
    if(flag == 1)
    {
      myservo.write(110);
      delay(500);
      sensorValue = digitalRead(Infrared);
      delay(100);
      Serial.print(sensorValue);
delay(10);
      if(sensorValue == 0)
      {
        flag++;  
      }
    
    }
    if(flag == 2)
    {
      myservo.write(70);
      delay(500);
      sensorValue = digitalRead(Infrared);
      delay(100);
      Serial.print(sensorValue);
delay(10);
      if(sensorValue == 1)
      {
        flag++;  
      }
    }
    if(flag == 3)
    {
      while(flag == 3)
      {
         digitalWrite(Led,LOW);       delay(100);
         Serial.print("      ");Serial.print(flag);
      }
       
    }


    
  }

}



void blink() {
flag = 1;Serial.print("      ");
Serial.print(flag); digitalWrite(Led,HIGH);   

}
