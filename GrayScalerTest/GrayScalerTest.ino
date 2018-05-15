//本历程为灰度传感器测试程序
#include <Servo.h>

Servo myservo;  // create servo 
int Light= 14;
int Led = 11;
int sensorValue = 0;
int flag = 0;
const byte interruptPin = 2;
int value1=0,value2=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(Light,INPUT);
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
      myservo.write(90);
      delay(500);
      sensorValue = analogRead(Light);
      delay(100);
      Serial.print(sensorValue);
delay(10);
  value1 = sensorValue;
  flag++;
/*      if(sensorValue > 510 && sensorValue < 550)
      {
        flag++;  
      }
  */  
    }
    if(flag == 2)
    {
      myservo.write(0);
      delay(500);
      sensorValue = analogRead(Light);
      delay(100);
      Serial.print(sensorValue);
delay(10);

value2 = sensorValue;
  if(value1 - value2 >45)
  flag++;
  /*    if(sensorValue > 450 && sensorValue < 490)
      {
        flag++;  
      }*/
    }
    if(flag == 3)
    {
      while(flag == 3)
      {
         digitalWrite(Led,LOW);       delay(1000);
         Serial.print("      ");Serial.print(flag);
      }
       
    }


    
  }

}



void blink() {
flag = 1;Serial.print("      ");
Serial.print(flag); digitalWrite(Led,HIGH);   

}
